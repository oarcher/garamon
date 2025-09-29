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
#include <vector>   // For Mvec_get_grades
#include <iostream> // For Mvec_display

using namespace project_namespace;

// Private definition of the opaque Mvec_C
struct Mvec_C
{
    project_namespace::Mvec<double> *p;
};

static Mvec_C *wrap(project_namespace::Mvec<double> *ptr)
{
    Mvec_C *h = new Mvec_C;
    h->p = ptr;
    return h;
}

// --- Constructors and Destructor ---

Mvec_C *Mvec_new_empty(void)
{
    return wrap(new Mvec<double>());
}

Mvec_C *Mvec_new_copy(const Mvec_C *mv)
{
    return wrap(new Mvec<double>(*mv->p));
}

Mvec_C *Mvec_new_scalar(double val)
{
    return wrap(new Mvec<double>(val));
}

void Mvec_delete(Mvec_C *mv)
{
    delete mv->p;
    delete mv;
}

// --- Assignment Operators ---

void Mvec_assign_copy(Mvec_C *dest, const Mvec_C *src)
{
    *(dest->p) = *(src->p);
}

// --- Arithmetic Operators ---

Mvec_C *Mvec_add(const Mvec_C *mv1, const Mvec_C *mv2)
{
    return wrap(new Mvec<double>(*mv1->p + *mv2->p));
}

Mvec_C *Mvec_add_scalar(const Mvec_C *mv, double value)
{
    return wrap(new Mvec<double>(*mv->p + value));
}

// Mvec_C *Mvec_scalar_add(double value, const Mvec_C *mv)
// {
//     return wrap(new Mvec<double>(value + *mv->p));
// }

void Mvec_add_assign(Mvec_C *dest, const Mvec_C *src)
{
    *(dest->p) += *(src->p);
}

Mvec_C *Mvec_negate(const Mvec_C *mv)
{
    return wrap(new Mvec<double>(-(*mv->p)));
}

Mvec_C *Mvec_sub(const Mvec_C *mv1, const Mvec_C *mv2)
{
    return wrap(new Mvec<double>(*mv1->p - *mv2->p));
}

Mvec_C *Mvec_sub_scalar(const Mvec_C *mv, double value)
{
    return wrap(new Mvec<double>(*mv->p - value));
}

// Mvec_C *Mvec_scalar_sub(double value, const Mvec_C *mv)
// {
//     return wrap(new Mvec<double>(value - *mv->p));
// }

void Mvec_sub_assign(Mvec_C *dest, const Mvec_C *src)
{
    *(dest->p) -= *(src->p);
}

// --- Geometric Product Operators ---

Mvec_C *Mvec_mul(const Mvec_C *mv1, const Mvec_C *mv2)
{
    return wrap(new Mvec<double>(*mv1->p * *mv2->p));
}

Mvec_C *Mvec_mul_scalar(const Mvec_C *mv, double value)
{
    return wrap(new Mvec<double>(*mv->p * value));
}

Mvec_C *Mvec_scalar_mul(double value, const Mvec_C *mv)
{
    return wrap(new Mvec<double>(value * *mv->p));
}

void Mvec_mul_assign(Mvec_C *dest, const Mvec_C *src)
{
    *(dest->p) *= *(src->p);
}

Mvec_C *Mvec_div(const Mvec_C *mv1, const Mvec_C *mv2)
{
    return wrap(new Mvec<double>(*mv1->p / *mv2->p));
}

Mvec_C *Mvec_div_scalar(const Mvec_C *mv, double value)
{
    return wrap(new Mvec<double>(*mv->p / value));
}

Mvec_C *Mvec_scalar_div(double value, const Mvec_C *mv)
{
    return wrap(new Mvec<double>(value / *mv->p));
}

void Mvec_div_assign(Mvec_C *dest, const Mvec_C *src)
{
    *(dest->p) /= *(src->p);
}

void Mvec_div_assign_scalar(Mvec_C *dest, double value)
{
    *(dest->p) /= value;
}

// --- Outer Product Operators ---

Mvec_C *Mvec_outer(const Mvec_C *mv1, const Mvec_C *mv2)
{
    return wrap(new Mvec<double>(*mv1->p ^ *mv2->p));
}

Mvec_C *Mvec_outer_scalar(const Mvec_C *mv, double value)
{
    return wrap(new Mvec<double>(*mv->p ^ value));
}

Mvec_C *Mvec_scalar_outer(double value, const Mvec_C *mv)
{
    return wrap(new Mvec<double>(value ^ *mv->p));
}

void Mvec_outer_assign(Mvec_C *dest, const Mvec_C *src)
{
    *(dest->p) ^= *(src->p);
}

// --- Inner Product Operators ---

Mvec_C *Mvec_inner(const Mvec_C *mv1, const Mvec_C *mv2)
{
    return wrap(new Mvec<double>(*mv1->p | *mv2->p));
}

Mvec_C *Mvec_inner_scalar(const Mvec_C *mv, double value)
{
    return wrap(new Mvec<double>(*mv->p | value));
}

Mvec_C *Mvec_scalar_inner(double value, const Mvec_C *mv)
{
    return wrap(new Mvec<double>(value | *mv->p));
}

void Mvec_inner_assign(Mvec_C *dest, const Mvec_C *src)
{
    *(dest->p) |= *(src->p);
}

// --- Contraction Operators ---

Mvec_C *Mvec_right_contraction(const Mvec_C *mv1, const Mvec_C *mv2)
{
    return wrap(new Mvec<double>(*mv1->p > *mv2->p));
}

Mvec_C *Mvec_right_contraction_scalar(const Mvec_C *mv, double value)
{
    return wrap(new Mvec<double>(*mv->p > value));
}

Mvec_C *Mvec_scalar_right_contraction(double value, const Mvec_C *mv)
{
    return wrap(new Mvec<double>(value > *mv->p));
}

Mvec_C *Mvec_left_contraction(const Mvec_C *mv1, const Mvec_C *mv2)
{
    return wrap(new Mvec<double>(*mv1->p < *mv2->p));
}

Mvec_C *Mvec_left_contraction_scalar(const Mvec_C *mv, double value)
{
    return wrap(new Mvec<double>(*mv->p < value));
}

Mvec_C *Mvec_scalar_left_contraction(double value, const Mvec_C *mv)
{
    return wrap(new Mvec<double>(value < *mv->p));
}

// --- Other Mvec Methods ---

Mvec_C *Mvec_reverse(const Mvec_C *mv)
{
    return wrap(new Mvec<double>(~(*mv->p)));
}

bool Mvec_equals(const Mvec_C *mv1, const Mvec_C *mv2)
{
    return *(mv1->p) == *(mv2->p);
}

Mvec_C *Mvec_inv(const Mvec_C *mv)
{
    return wrap(new Mvec<double>(mv->p->inv()));
}

bool Mvec_not_equals(const Mvec_C *mv1, const Mvec_C *mv2)
{
    return *(mv1->p) != *(mv2->p);
}

double Mvec_to_scalar(const Mvec_C *mv)
{
    return static_cast<double>(*(mv->p));
}

double Mvec_get_coeff(const Mvec_C *mv, int idx)
{
    return (*mv->p)[idx];
}

void Mvec_set_coeff(Mvec_C *mv, int idx, double value)
{
    (*mv->p)[idx] = value;
}

Mvec_C *Mvec_component_to_one(unsigned int grade, int index)
{
    Mvec<double> temp_mv;
    return wrap(new Mvec<double>(temp_mv.componentToOne(grade, index)));
}

double Mvec_norm(const Mvec_C *mv)
{
    return mv->p->norm();
}

double Mvec_quadratic_norm(const Mvec_C *mv)
{
    return mv->p->quadraticNorm();
}

int Mvec_get_highest_grade(const Mvec_C *mv)
{
    return mv->p->grade();
}

// FIXME: do not use malloc (copy to pre allocated array ?))
unsigned int *Mvec_get_grades(const Mvec_C *mv, int *count)
{
    std::vector<unsigned int> grades_vec = mv->p->grades();
    *count = grades_vec.size();
    unsigned int *grades_array = (unsigned int *)malloc(sizeof(unsigned int) * (*count));
    for (int i = 0; i < *count; ++i)
    {
        grades_array[i] = grades_vec[i];
    }
    return grades_array;
}

Mvec_C *Mvec_get_grade_component(const Mvec_C *mv, int grade)
{
    return wrap(new Mvec<double>(mv->p->grade(grade)));
}

bool Mvec_is_grade(const Mvec_C *mv, unsigned int grade)
{
    return mv->p->isGrade(grade);
}

void Mvec_clear(Mvec_C *mv, int grade)
{
    mv->p->clear(grade);
}

bool Mvec_is_empty(const Mvec_C *mv)
{
    return mv->p->isEmpty();
}

bool Mvec_is_homogeneous(const Mvec_C *mv)
{
    return mv->p->isHomogeneous();
}

void Mvec_round_zero(Mvec_C *mv, double epsilon)
{
    mv->p->roundZero(epsilon);
}

bool Mvec_same_grade(const Mvec_C *mv1, const Mvec_C *mv2)
{
    return mv1->p->sameGrade(*mv2->p);
}

void Mvec_display(const Mvec_C *mv)
{
    std::cout << *(mv->p) << std::endl;
}

Mvec_C *Mvec_extract_one_component(const Mvec_C *mv, int grade, int sizeOfKVector, int indexInKvector)
{
    return wrap(new Mvec<double>(mv->p->extractOneComponent(grade, sizeOfKVector, indexInKvector)));
}

// Additional functions
Mvec_C *Mvec_left_contraction_func(const Mvec_C *mv1, const Mvec_C *mv2)
{
    return wrap(new Mvec<double>(leftContraction(*mv1->p, *mv2->p)));
}

Mvec_C *Mvec_right_contraction_func(const Mvec_C *mv1, const Mvec_C *mv2)
{
    return wrap(new Mvec<double>(rightContraction(*mv1->p, *mv2->p)));
}

Mvec_C *Mvec_I(void)
{
    return wrap(new Mvec<double>(I<double>()));
}

Mvec_C *Mvec_Iinv(void)
{
    return wrap(new Mvec<double>(Iinv<double>()));
}

Mvec_C *Mvec_scalar_product(const Mvec_C *mv1, const Mvec_C *mv2)
{
    return wrap(new Mvec<double>(mv1->p->scalarProduct(*mv2->p)));
}

Mvec_C *Mvec_dot_product(const Mvec_C *mv1, const Mvec_C *mv2)
{
    return wrap(new Mvec<double>(mv1->p->dotProduct(*mv2->p)));
}


project_singular_metric_comment_begin

Mvec_C *Mvec_outer_primal_dual(const Mvec_C *mv1, const Mvec_C *mv2)
{
    return wrap(new Mvec<double>(mv1->p->outerPrimalDual(*mv2->p)));
}

Mvec_C *Mvec_outer_dual_primal(const Mvec_C *mv1, const Mvec_C *mv2)
{
    return wrap(new Mvec<double>(mv1->p->outerDualPrimal(*mv2->p)));
}

Mvec_C *Mvec_outer_dual_dual(const Mvec_C *mv1, const Mvec_C *mv2)
{
    return wrap(new Mvec<double>(mv1->p->outerDualDual(*mv2->p)));
}

Mvec_C *Mvec_dual(const Mvec_C *mv)
{
    return wrap(new Mvec<double>(!(*mv->p)));
}

project_singular_metric_comment_end

// --- Basis vector accessors ----

project_static_multivector_one_component