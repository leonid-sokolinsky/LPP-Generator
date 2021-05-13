/*==============================================================================
Project: VaLiPro
Theme: LPP Generator
Module: Problem-Data.h (Problem Data)
Prefix: PD
Author: Leonid B. Sokolinsky
==============================================================================*/
#include "Problem-Types.h"			// Problem Parameters 
using namespace std;

//========================== Problem variables ====================================
static int PD_n;
static int PD_m;
static int PD_NumOfRndInequalities;
static int PD_k;	// Index of current random inequality
static PT_float_T PD_centerObjectF;	// Value of object function in the center of hypercube
static unsigned PD_failuresType1 = 0;
static unsigned PD_failuresType2 = 0;
static unsigned PD_failuresType3 = 0;

//========================== Problem data structures ==============================
static PT_matrix_T PD_A;
static PT_column_T PD_b;
static PT_vector_T PD_c;
static PT_vector_T PD_center;		// Center of hypercube
static PT_column_T PD_aNorm;

//========================== Files ==============================
static string PD_fileName;