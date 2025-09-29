// Copyright (c) 2018 by University Paris-Est Marne-la-Vallee
// Mvec.h
// This file is part of the Garamon for project_namespace.
// Authors: Stephane Breuils and Vincent Nozick
// Contact: vincent.nozick@u-pem.fr
//
// Licence MIT
// A a copy of the MIT License is given along with this program

/// \file Mvec.h
/// \author Stephane Breuils, Vincent Nozick
/// \brief C wrapper for the Mvec class in the Geometric algebra of project_namespace.

#ifndef project_inclusion_guard
#define project_inclusion_guard

#include <stdbool.h>

#ifdef __cplusplus
extern "C"
{
#endif

project_basis_vector_index

    // Opaque struct for Mvec
    typedef struct Mvec_C Mvec_C;

    // --- Constructors and Destructor ---
    Mvec_C *Mvec_new_empty(void);
    Mvec_C *Mvec_new_copy(const Mvec_C *mv);
    Mvec_C *Mvec_new_scalar(double val);
    void Mvec_delete(Mvec_C *mv);

    // --- Assignment Operators ---
    void Mvec_assign_copy(Mvec_C *dest, const Mvec_C *src);

    // --- Arithmetic Operators ---
    Mvec_C *Mvec_add(const Mvec_C *mv1, const Mvec_C *mv2);
    Mvec_C *Mvec_add_scalar(const Mvec_C *mv, double value);
    // Mvec_C *Mvec_scalar_add(double value, const Mvec_C *mv);
    void Mvec_add_assign(Mvec_C *dest, const Mvec_C *src);
    Mvec_C *Mvec_negate(const Mvec_C *mv);
    Mvec_C *Mvec_sub(const Mvec_C *mv1, const Mvec_C *mv2);
    Mvec_C *Mvec_sub_scalar(const Mvec_C *mv, double value);
    // Mvec_C *Mvec_scalar_sub(double value, const Mvec_C *mv);
    void Mvec_sub_assign(Mvec_C *dest, const Mvec_C *src);

    // --- Geometric Product Operators ---
    Mvec_C *Mvec_mul(const Mvec_C *mv1, const Mvec_C *mv2);
    Mvec_C *Mvec_mul_scalar(const Mvec_C *mv, double value);
    Mvec_C *Mvec_scalar_mul(double value, const Mvec_C *mv);
    void Mvec_mul_assign(Mvec_C *dest, const Mvec_C *src);
    Mvec_C *Mvec_div(const Mvec_C *mv1, const Mvec_C *mv2);
    Mvec_C *Mvec_div_scalar(const Mvec_C *mv, double value);
    Mvec_C *Mvec_scalar_div(double value, const Mvec_C *mv);
    void Mvec_div_assign(Mvec_C *dest, const Mvec_C *src);
    void Mvec_div_assign_scalar(Mvec_C *dest, double value);

    // --- Outer Product Operators ---
    Mvec_C *Mvec_outer(const Mvec_C *mv1, const Mvec_C *mv2);
    Mvec_C *Mvec_outer_scalar(const Mvec_C *mv, double value);
    Mvec_C *Mvec_scalar_outer(double value, const Mvec_C *mv);
    void Mvec_outer_assign(Mvec_C *dest, const Mvec_C *src);

    // --- Inner Product Operators ---
    Mvec_C *Mvec_inner(const Mvec_C *mv1, const Mvec_C *mv2);
    Mvec_C *Mvec_inner_scalar(const Mvec_C *mv, double value);
    Mvec_C *Mvec_scalar_inner(double value, const Mvec_C *mv);
    void Mvec_inner_assign(Mvec_C *dest, const Mvec_C *src);

    // --- Contraction Operators ---
    Mvec_C *Mvec_right_contraction(const Mvec_C *mv1, const Mvec_C *mv2);
    Mvec_C *Mvec_right_contraction_scalar(const Mvec_C *mv, double value);
    Mvec_C *Mvec_scalar_right_contraction(double value, const Mvec_C *mv);
    Mvec_C *Mvec_left_contraction(const Mvec_C *mv1, const Mvec_C *mv2);
    Mvec_C *Mvec_left_contraction_scalar(const Mvec_C *mv, double value);
    Mvec_C *Mvec_scalar_left_contraction(double value, const Mvec_C *mv);

    // --- Other Mvec Methods ---
    Mvec_C *Mvec_reverse(const Mvec_C *mv);
    bool Mvec_equals(const Mvec_C *mv1, const Mvec_C *mv2);
    Mvec_C *Mvec_inv(const Mvec_C *mv);
    bool Mvec_not_equals(const Mvec_C *mv1, const Mvec_C *mv2);
    double Mvec_to_scalar(const Mvec_C *mv);
    double Mvec_get_coeff(const Mvec_C *mv, int idx);
    void Mvec_set_coeff(Mvec_C *mv, int idx, double value);
    Mvec_C *Mvec_component_to_one(unsigned int grade, int index);
    double Mvec_norm(const Mvec_C *mv);
    double Mvec_quadratic_norm(const Mvec_C *mv);
    int Mvec_get_highest_grade(const Mvec_C *mv);
    unsigned int *Mvec_get_grades(const Mvec_C *mv, int *count);
    Mvec_C *Mvec_get_grade_component(const Mvec_C *mv, int grade);
    bool Mvec_is_grade(const Mvec_C *mv, unsigned int grade);
    void Mvec_clear(Mvec_C *mv, int grade);
    bool Mvec_is_empty(const Mvec_C *mv);
    bool Mvec_is_homogeneous(const Mvec_C *mv);
    void Mvec_round_zero(Mvec_C *mv, double epsilon);
    bool Mvec_same_grade(const Mvec_C *mv1, const Mvec_C *mv2);
    void Mvec_display(const Mvec_C *mv);
    Mvec_C *Mvec_extract_one_component(const Mvec_C *mv, int grade, int sizeOfKVector, int indexInKvector);

    // Basis vector accessors
project_static_multivector_one_component

    // Additional functions
    Mvec_C *Mvec_left_contraction_func(const Mvec_C *mv1, const Mvec_C *mv2);
    Mvec_C *Mvec_right_contraction_func(const Mvec_C *mv1, const Mvec_C *mv2);
    Mvec_C *Mvec_I(void);
    Mvec_C *Mvec_Iinv(void);
    Mvec_C *Mvec_scalar_product(const Mvec_C *mv1, const Mvec_C *mv2);
    Mvec_C *Mvec_dot_product(const Mvec_C *mv1, const Mvec_C *mv2);

project_singular_metric_comment_begin
    Mvec_C *Mvec_outer_primal_dual(const Mvec_C *mv1, const Mvec_C *mv2);
    Mvec_C *Mvec_outer_dual_primal(const Mvec_C *mv1, const Mvec_C *mv2);
    Mvec_C *Mvec_outer_dual_dual(const Mvec_C *mv1, const Mvec_C *mv2);
    Mvec_C *Mvec_dual(const Mvec_C *mv);
project_singular_metric_comment_end

#ifdef __cplusplus
}
#endif

#endif // project_inclusion_guard