/*==============================================================================
Project: LiFe
Theme: LPP Generator
Module: Parameters of LPP Generator
Prefix: ISG
Author: Leonid B. Sokolinsky
==============================================================================*/
#define ISG_N 4													// Space dimension	
#define ISG_NUM_OF_NATURAL_INEQUALITIES (ISG_N)					// Number of natural inequalities		|
#define ISG_FILE "C:/Temp/lpp-1.txt"							// File to save LPP
#define	ISG_MAX_LIKE 2.5										// Maximal acceptable likeness of equations
#define	ISG_MIN_SHIFT (ISG_MAX_LIKE*10)							// Minimal acceptable shift
#define ISG_M (2*ISG_N + ISG_NUM_OF_NATURAL_INEQUALITIES + 1)	// Total number of inequalities
#define ISG_ALPHA 200											// Length of hypercube edge
#define ISG_RHO (ISG_ALPHA/2)									// Radius of large hypersphere
#define ISG_THETA (ISG_RHO/4)									// Radius of small hypersphere