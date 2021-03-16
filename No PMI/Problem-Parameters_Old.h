/*==============================================================================
Project: LiFe
Theme: LPP Generator
Module: Problem-Parameters.h (Problem Parameters)
Prefix: PP
Author: Leonid B. Sokolinsky
==============================================================================*/

//=========================== Problem Parameters =========================
#define PP_MAX_N 10											// Maximal Space dimension	
#define PP_MAX_NUM_OF_RND_INEQUALITIES (PP_MAX_N)			// Maximal Number of random inequalities		|
#define PP_FILE "lpp.txt"									// File to save LPP
#define PP_MAX_M (2*PP_MAX_N + PP_MAX_NUM_OF_RND_INEQUALITIES + 1)	// Maximal Total number of inequalities
#define PP_ALPHA 200										// Length of hypercube edge
#define PP_RHO (PP_ALPHA/2)									// Radius of large hypersphere
#define PP_THETA (PP_RHO/2)									// Radius of small hypersphere
#define	PP_A_MAX (PP_ALPHA*5)								// Maximal random value for A
#define	PP_B_MAX (PP_ALPHA*50)								// Maximal random value for b
#define	PP_MAX_LIKE 0.35									// Maximal acceptable likeness of equations (must be less then 1.4)
#define	PP_MIN_SHIFT (PP_RHO)								// Minimal acceptable shift
//-------------------------- Outpoot Parameters ---------------------------
#define PP_OUTPUT_LIMIT	11	// Number of Elements to output
#define PP_SETW 8
#define PP_MATRIX_OUTPUT	
#define PP_FILE_OUTPUT