/*==============================================================================
Project: LiFe
Theme: LPP Generator
Module: Application Programming Interface
Prefix: ISG
Author: Leonid B. Sokolinsky
==============================================================================*/
#include "ISG-Types.h"	// Definition of ISG_float_T

void ISG_Init();		// Initialization 

void ISG_GenRndLPP(ISG_matrix_T A, ISG_column_T b, ISG_vector_T c);
/* Generate random LPP
System: Ax <= b
Obgective function: <c,x>
*/

void ISG_GenMdlLPP(ISG_matrix_T A, ISG_column_T b, ISG_vector_T c);
/* Generate "model" LPP
System: Ax <= b
------------------------------------------------------------
 x_0								<= alpha
		 x_1						<= alpha
				 ...
						 x_{n-1}	<= alpha
 x_0	+x_1	+...	+x_{n-1}	<= alpha*(n-1) + alpha/2
-x_0								<= alpha
		-x_1						<= alpha
				 ...
						-x_{n-1}	<= alpha
------------------------------------------------------------
Obgective function: <c,x> = 10*n*x_0 + 10*(n-1)*x_1 + ... + 10*x_{n-1}
This LPP has the following unique solution:
x = (alpha,...,alpha,alpha/2)
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