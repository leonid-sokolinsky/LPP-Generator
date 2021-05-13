/*==============================================================================
Project: VaLiPro
Theme: LPP Generator
Module: Problem-Types.h (Problem Types)
Prefix: PT
Author: Leonid B. Sokolinsky
==============================================================================*/
#pragma once
#include "Problem-Include.h"		// Problem "Include" Files
#include "Problem-Parameters.h"		// Problem Parameters 
//=========================== Problem Types =========================
typedef float PT_float_T;
typedef PT_float_T	PT_vector_T[PP_N];
typedef PT_float_T	PT_matrix_T[PP_M][PP_N];
typedef PT_float_T	PT_column_T[PP_M];