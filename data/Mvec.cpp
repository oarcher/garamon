// Copyright (c) 2018 by University Paris-Est Marne-la-Vallee
// Mvec.cpp
// This file is part of the Garamon for project_namespace.
// Authors: Stephane Breuils and Vincent Nozick
// Contact: vincent.nozick@u-pem.fr
//
// Licence MIT
// A a copy of the MIT License is given along with this program

/// \file Mvec.cpp
/// \author Stephane Breuils, Vincent Nozick
/// \brief C wrapper for the Mvec class in the Geometric algebra of project_namespace.

#include "project_namespace/Mvec.h"
#include "project_namespace/Mvec.hpp"
#include <cassert>  // For assert
#include <vector>   // For Mvec_get_grades
#include <iostream> // For Mvec_display



using namespace project_namespace;

// --- helpers: opaque handle <-> C++ type ----
static inline Mvec<double>*       to_impl(Mvec_C h)       { return reinterpret_cast<Mvec<double>*>(h); }
static inline Mvec<double> const* to_impl_c(Mvec_C h)     { return reinterpret_cast<Mvec<double> const*>(h); }
static inline Mvec_C              to_handle(Mvec<double>* p){ return reinterpret_cast<Mvec_C>(p); }


// All exported C functions
extern "C" {

// --- Constructors and Destructor ---

Mvec_C Mvec_new_empty(void)
{
    return to_handle(new Mvec<double>());
}

Mvec_C Mvec_new_copy(Mvec_C mv)
{
    assert(mv);
    return to_handle(new Mvec<double>(*to_impl_c(mv)));
}

Mvec_C Mvec_new_scalar(double val)
{
    return to_handle(new Mvec<double>(val));
}

void Mvec_delete(Mvec_C mv)
{
    delete to_impl(mv);
}

// --- Assignment Operators ---

void Mvec_assign_copy(Mvec_C dest, Mvec_C src)
{
    assert(dest && src);
    *to_impl(dest) = *to_impl_c(src);
}

// --- Arithmetic Operators ---

Mvec_C Mvec_add(Mvec_C mv1, Mvec_C mv2)
{
    assert(mv1 && mv2);
    return to_handle(new Mvec<double>(*to_impl_c(mv1) + *to_impl_c(mv2)));
}

Mvec_C Mvec_add_scalar(Mvec_C mv, double value)
{
    assert(mv);
    return to_handle(new Mvec<double>(*to_impl_c(mv) + value));
}

// Mvec_C Mvec_scalar_add(double value, Mvec_C mv)
// {
//     assert(mv);
//     return to_handle(new Mvec<double>(value + *to_impl_c(mv)));
// }

void Mvec_add_assign(Mvec_C dest, Mvec_C src)
{
    assert(dest && src);
    *to_impl(dest) += *to_impl_c(src);
}

Mvec_C Mvec_negate(Mvec_C mv)
{
    assert(mv);
    return to_handle(new Mvec<double>(-*to_impl_c(mv)));
}

Mvec_C Mvec_sub(Mvec_C mv1, Mvec_C mv2)
{
    assert(mv1 && mv2);
    return to_handle(new Mvec<double>(*to_impl_c(mv1) - *to_impl_c(mv2)));
}

Mvec_C Mvec_sub_scalar(Mvec_C mv, double value)
{
    assert(mv);
    return to_handle(new Mvec<double>(*to_impl_c(mv) - value));
}

// Mvec_C Mvec_scalar_sub(double value, Mvec_C mv)
// {
//     assert(mv);
//     return to_handle(new Mvec<double>(value - *to_impl_c(mv)));
// }

void Mvec_sub_assign(Mvec_C dest, Mvec_C src)
{
    assert(dest && src);
    *to_impl(dest) -= *to_impl_c(src);
}

// --- Geometric Product Operators ---

Mvec_C Mvec_mul(Mvec_C mv1, Mvec_C mv2)
{
    assert(mv1 && mv2);
    return to_handle(new Mvec<double>(*to_impl_c(mv1) * *to_impl_c(mv2)));
}

Mvec_C Mvec_mul_scalar(Mvec_C mv, double value)
{
    assert(mv);
    return to_handle(new Mvec<double>(*to_impl_c(mv) * value));
}

Mvec_C Mvec_scalar_mul(double value, Mvec_C mv)
{
    assert(mv);
    return to_handle(new Mvec<double>(value * *to_impl_c(mv)));
}

void Mvec_mul_assign(Mvec_C dest, Mvec_C src)
{
    assert(dest && src);
    *to_impl(dest) *= *to_impl_c(src);
}

Mvec_C Mvec_div(Mvec_C mv1, Mvec_C mv2)
{
    assert(mv1 && mv2);
    return to_handle(new Mvec<double>(*to_impl_c(mv1) / *to_impl_c(mv2)));
}

Mvec_C Mvec_div_scalar(Mvec_C mv, double value)
{
    assert(mv);
    return to_handle(new Mvec<double>(*to_impl_c(mv) / value));
}

Mvec_C Mvec_scalar_div(double value, Mvec_C mv)
{
    assert(mv);
    return to_handle(new Mvec<double>(value / *to_impl_c(mv)));
}

void Mvec_div_assign(Mvec_C dest, Mvec_C src)
{
    assert(dest && src);
    *to_impl(dest) /= *to_impl_c(src);
}

void Mvec_div_assign_scalar(Mvec_C dest, double value)
{
    assert(dest);
    *to_impl(dest) /= value;
}

// --- Outer Product Operators ---

Mvec_C Mvec_outer(Mvec_C mv1, Mvec_C mv2)
{
    assert(mv1 && mv2);
    return to_handle(new Mvec<double>(*to_impl_c(mv1) ^ *to_impl_c(mv2)));
}

Mvec_C Mvec_outer_scalar(Mvec_C mv, double value)
{
    assert(mv);
    return to_handle(new Mvec<double>(*to_impl_c(mv) ^ value));
}

Mvec_C Mvec_scalar_outer(double value, Mvec_C mv)
{
    assert(mv);
    return to_handle(new Mvec<double>(value ^ *to_impl_c(mv)));
}

void Mvec_outer_assign(Mvec_C dest, Mvec_C src)
{
    assert(dest && src);
    *to_impl(dest) ^= *to_impl_c(src);
}

// --- Inner Product Operators ---

Mvec_C Mvec_inner(Mvec_C mv1, Mvec_C mv2)
{
    assert(mv1 && mv2);
    return to_handle(new Mvec<double>(*to_impl_c(mv1) | *to_impl_c(mv2)));
}

Mvec_C Mvec_inner_scalar(Mvec_C mv, double value)
{
    assert(mv);
    return to_handle(new Mvec<double>(*to_impl_c(mv) | value));
}

Mvec_C Mvec_scalar_inner(double value, Mvec_C mv)
{
    assert(mv);
    return to_handle(new Mvec<double>(value | *to_impl_c(mv)));
}

void Mvec_inner_assign(Mvec_C dest, Mvec_C src)
{
    assert(dest && src);
    *to_impl(dest) |= *to_impl_c(src);
}

// --- Contraction Operators ---

Mvec_C Mvec_right_contraction(Mvec_C mv1, Mvec_C mv2)
{
    assert(mv1 && mv2);
    return to_handle(new Mvec<double>(*to_impl_c(mv1) > *to_impl_c(mv2)));
}

Mvec_C Mvec_right_contraction_scalar(Mvec_C mv, double value)
{
    assert(mv);
    return to_handle(new Mvec<double>(*to_impl_c(mv) > value));
}

Mvec_C Mvec_scalar_right_contraction(double value, Mvec_C mv)
{
    assert(mv);
    return to_handle(new Mvec<double>(value > *to_impl_c(mv)));
}

Mvec_C Mvec_left_contraction(Mvec_C mv1, Mvec_C mv2)
{
    assert(mv1 && mv2);
    return to_handle(new Mvec<double>(*to_impl_c(mv1) < *to_impl_c(mv2)));
}

Mvec_C Mvec_left_contraction_scalar(Mvec_C mv, double value)
{
    assert(mv);
    return to_handle(new Mvec<double>(*to_impl_c(mv) < value));
}

Mvec_C Mvec_scalar_left_contraction(double value, Mvec_C mv)
{
    assert(mv);
    return to_handle(new Mvec<double>(value < *to_impl_c(mv)));
}

// --- Other Mvec Methods ---

Mvec_C Mvec_reverse(Mvec_C mv)
{
    assert(mv);
    return to_handle(new Mvec<double>(~(*to_impl_c(mv))));
}

bool Mvec_equals(Mvec_C mv1, Mvec_C mv2)
{
    assert(mv1 && mv2);
    return *to_impl_c(mv1) == *to_impl_c(mv2);
}

Mvec_C Mvec_inv(Mvec_C mv)
{
    assert(mv);
    return to_handle(new Mvec<double>(to_impl_c(mv)->inv()));
}

bool Mvec_not_equals(Mvec_C mv1, Mvec_C mv2)
{
    assert(mv1 && mv2);
    return *to_impl_c(mv1) != *to_impl_c(mv2);
}

double Mvec_to_scalar(Mvec_C mv)
{
    assert(mv);
    return (*to_impl_c(mv))[scalar];
}

double Mvec_get_coeff(Mvec_C mv, int idx)
{
    assert(mv);
    return (*to_impl_c(mv))[idx];
}

void Mvec_set_coeff(Mvec_C mv, int idx, double value)
{
    assert(mv);
    (*to_impl(mv))[idx] = value;
}

Mvec_C Mvec_component_to_one(unsigned int grade, int index)
{
    Mvec<double> temp_mv;
    return to_handle(new Mvec<double>(temp_mv.componentToOne(grade, index)));
}

double Mvec_norm(Mvec_C mv)
{
    assert(mv);
    return to_impl_c(mv)->norm();
}

double Mvec_quadratic_norm(Mvec_C mv)
{
    assert(mv);
    return to_impl_c(mv)->quadraticNorm();
}

int Mvec_get_highest_grade(Mvec_C mv)
{
    assert(mv);
    return to_impl_c(mv)->grade();
}

unsigned int Mvec_get_grades_count(const Mvec_C mv)
{
    assert(mv);
    return static_cast<int>(to_impl_c(mv)->grades().size());
}

/// \brief copy grades vector to *out (out must be pre allocated)
int Mvec_copy_grades(Mvec_C mv, unsigned int* out, int cap) {
    assert(mv && out && cap > 0);
    const auto& v = to_impl_c(mv)->grades();
    const int n = static_cast<int>(v.size());
    const int w = std::min(n, cap);
    for (int i = 0; i < w; ++i) out[i] = v[static_cast<size_t>(i)];
    return w;
}

Mvec_C Mvec_get_grade_component(Mvec_C mv, int grade)
{
    assert(mv);
    return to_handle(new Mvec<double>(to_impl_c(mv)->grade(grade)));
}

bool Mvec_is_grade(Mvec_C mv, unsigned int grade)
{
    assert(mv);
    return to_impl_c(mv)->isGrade(grade);
}

void Mvec_clear(Mvec_C mv, int grade)
{
    assert(mv);
    to_impl(mv)->clear(grade);
}

bool Mvec_is_empty(Mvec_C mv)
{
    assert(mv);
    return to_impl_c(mv)->isEmpty();
}

bool Mvec_is_homogeneous(Mvec_C mv)
{
    assert(mv);
    return to_impl_c(mv)->isHomogeneous();
}

void Mvec_round_zero(Mvec_C mv, double epsilon)
{
    assert(mv);
    to_impl(mv)->roundZero(epsilon);
}

bool Mvec_same_grade(Mvec_C mv1, Mvec_C mv2)
{
    assert(mv1 && mv2);
    return to_impl_c(mv1)->sameGrade(*to_impl_c(mv2));
}

void Mvec_display(Mvec_C mv)
{
    assert(mv);
    std::cout << *to_impl_c(mv) << std::endl;
}

Mvec_C Mvec_extract_one_component(Mvec_C mv, int grade, int sizeOfKVector, int indexInKvector)
{
    assert(mv);
    return to_handle(new Mvec<double>(to_impl_c(mv)->extractOneComponent(grade, sizeOfKVector, indexInKvector)));
}

// Additional functions
Mvec_C Mvec_left_contraction_func(Mvec_C mv1, Mvec_C mv2)
{
    assert(mv1 && mv2);
    return to_handle(new Mvec<double>(leftContraction(*to_impl_c(mv1), *to_impl_c(mv2))));
}

Mvec_C Mvec_right_contraction_func(Mvec_C mv1, Mvec_C mv2)
{
    assert(mv1 && mv2);
    return to_handle(new Mvec<double>(rightContraction(*to_impl_c(mv1), *to_impl_c(mv2))));
}

Mvec_C Mvec_I(void)
{
    return to_handle(new Mvec<double>(I<double>()));
}

project_singular_metric_comment_begin
Mvec_C Mvec_Iinv(void)
{
    return to_handle(new Mvec<double>(Iinv<double>()));
}
project_singular_metric_comment_end

Mvec_C Mvec_scalar_product(Mvec_C mv1, Mvec_C mv2)
{
    assert(mv1 && mv2);
    return to_handle(new Mvec<double>(to_impl_c(mv1)->scalarProduct(*to_impl_c(mv2))));
}

Mvec_C Mvec_dot_product(Mvec_C mv1, Mvec_C mv2)
{
    assert(mv1 && mv2);
    return to_handle(new Mvec<double>(to_impl_c(mv1)->dotProduct(*to_impl_c(mv2))));
}


project_singular_metric_comment_begin

Mvec_C Mvec_outer_primal_dual(Mvec_C mv1, Mvec_C mv2)
{
    assert(mv1 && mv2);
    return to_handle(new Mvec<double>(to_impl_c(mv1)->outerPrimalDual(*to_impl_c(mv2))));
}

Mvec_C Mvec_outer_dual_primal(Mvec_C mv1, Mvec_C mv2)
{
    assert(mv1 && mv2);
    return to_handle(new Mvec<double>(to_impl_c(mv1)->outerDualPrimal(*to_impl_c(mv2))));
}

Mvec_C Mvec_outer_dual_dual(Mvec_C mv1, Mvec_C mv2)
{
    assert(mv1 && mv2);
    return to_handle(new Mvec<double>(to_impl_c(mv1)->outerDualDual(*to_impl_c(mv2))));
}

Mvec_C Mvec_dual(Mvec_C mv)
{
    assert(mv);
    return to_handle(new Mvec<double>(!(*to_impl_c(mv))));
}

project_singular_metric_comment_end

// --- Basis vector accessors ----

project_static_multivector_one_component


} // extern "C"