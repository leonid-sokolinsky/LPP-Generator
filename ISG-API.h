/*==============================================================================
Project: LiFe
Theme: LPP Generator
Module: Application Programming Interface
Prefix: ISG
Author: Leonid B. Sokolinsky
==============================================================================*/
#include "ISG-Types.h"	// Definition of ISG_float_T

void ISG_Init();		// Initialization 

void ISG_GenLPP(ISG_matrix_T A, ISG_column_T b, ISG_vector_T c);
/* Generate random LPP
System: Ax <= b
Obgective function: <c,x>
*/

errno_t ISG_SaveLPP(ISG_matrix_T A, ISG_column_T b, ISG_vector_T c, const char* filename); 
/* Save LPP in the file using the following format: 
------------ begin of file -------------
m n
A_11 A_12 ... A_1n b_1
A_21 A_22 ... A_2n b_2
...
A_m1 A_m2 ... A_mn b_m
c_1 c_2 ... c_n
------------ end of file----------------
*/