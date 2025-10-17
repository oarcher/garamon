// Copyright (c) 2018 by University Paris-Est Marne-la-Vallee
// Mvec.cpp
// This file is part of the Garamon for project_namespace.
// Authors: Stephane Breuils and Vincent Nozick
// Contact: vincent.nozick@u-pem.fr
//
// Licence MIT
// A a copy of the MIT License is given along with this program

/// \file mini_generator.cpp
/// \author Stephane Breuils, Vincent Nozick, Olivier Archer
/// \brief Minimal template-based generator for C wrappers embedded in the generated algebra library.


// Note: this file must be processed by the main generator carfullly
// as it include templated string that should *not* be interpreted by the main generator

#include "project_namespace/Mvec.h"
#include "project_namespace/Mvec.hpp"
#include <cassert>
#include <regex>
#include <string>
#include <cstring>

using namespace project_namespace;

// Wraps the C-style X-macro BLADE_LIST into a C++ struct array (kBlades)
// so the generated blade data can be accessed and iterated easily at runtime.
// static const BladeInfo kBlades[] = {
//   {1,0,1,"0"},
//   {1,1,2,"1"},
//   ...
//   {7,0,127,"012345i"}
// };
struct BladeInfo { unsigned grade; unsigned pos; unsigned xorIndex; const char* name; };
#define X(g,p,x,n) { (unsigned)(g), (unsigned)(p), (unsigned)(x), (n) },
static const BladeInfo kBlades[] = {
  BLADE_LIST(X)
};
#undef X

static const unsigned kBladeCount = (unsigned)(sizeof(kBlades)/sizeof(kBlades[0]));

inline std::string render_block_from_template(const std::string& tmpl) {
    std::string out; out.reserve(4096);
    for (unsigned i = 0; i < kBladeCount; ++i) {
        const BladeInfo& b = kBlades[i];
        std::string cur = tmpl;
        cur = std::regex_replace(cur, std::regex("project_name_blade"),                 b.name);
        cur = std::regex_replace(cur, std::regex("project_homogeneous_index_blade"),   std::to_string(b.pos));
        cur = std::regex_replace(cur, std::regex("project_xor_index_blade"),           std::to_string(b.xorIndex));
        cur = std::regex_replace(cur, std::regex("project_grade_blade"),               std::to_string(b.grade));
        out += cur;
    }
    return out;
}

// garamon_parser implements a simple template engine
// embededed in the generated library to allow basic code generation
extern "C" const char* garamon_parser(
    const char* data,
    const char* tmpl_one_component,
    const char* tmpl_constants
){
    if (!data || !tmpl_one_component || !tmpl_constants) return nullptr;

    try {
        std::string out(data);

        out = std::regex_replace(out, std::regex("project_namespace"),
                                 PROJECT_NAMESPACE);
        out = std::regex_replace(out, std::regex("project_first_vector_basis"),
                                 PROJECT_FIRST_VECTOR_BASIS);
        out = std::regex_replace(out, std::regex("project_second_vector_basis"),
                                 PROJECT_SECOND_VECTOR_BASIS);

        const std::string one  = render_block_from_template(std::string(tmpl_one_component));
        out = std::regex_replace(out, std::regex("project_static_multivector_one_component"), one);

        const std::string cons = render_block_from_template(std::string(tmpl_constants));
        out = std::regex_replace(out, std::regex("project_basis_vector_index"), cons);

        char* res = new char[out.size() + 1];
        std::memcpy(res, out.data(), out.size());
        res[out.size()] = '\0';
        return res;
    } catch (...) {
        return nullptr;
    }
}
