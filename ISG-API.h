/*==============================================================================
Project: LiFe
Theme: LPP Generator
Module: Application programming interface
Prefix: ISG
Author: Leonid B. Sokolinsky
==============================================================================*/
#include "ISG-Types.h"	// Definition of PT_float_T

void ISG_Init();		// Initialization 

void ISG_GenerateLPP	// LPP generator
(
	PT_matrix_T A,	// Matrix A
	PT_column_T b,	// Column b
	PT_vector_T c	// Coefficients of linear objective function
);