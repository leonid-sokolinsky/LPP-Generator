/*==============================================================================
Project: LiFe
Theme: LPP Generator
Module: Parameters of LPP Generator
Prefix: ISG
Author: Leonid B. Sokolinsky
==============================================================================*/
#define RANDOM_LPP											// Generate random LPP
#define ISG_N 8											// Space dimension	
#ifdef RANDOM_LPP
#define ISG_NUM_OF_NATURAL_INEQUALITIES (ISG_N*5)			// Number of natural inequalities for random LPP
#define ISG_FILE "C:/TEMP/rndLpp.txt"						// File to save a random LPP
#else
#define ISG_NUM_OF_NATURAL_INEQUALITIES 1					// Number of natural inequalities for model LPP
#define ISG_FILE "C:/TEMP/mdlLpp.txt"						// File to save a model LPP
#endif
#define ISG_M (2*ISG_N + ISG_NUM_OF_NATURAL_INEQUALITIES)	// Total number of inequalities
#define ISG_ALPHA 20										// Length of hypercube edge
#define ISG_RHO (ISG_ALPHA/2)								// Radius of large hypersphere
#define ISG_THETA (ISG_RHO/2)								// Radius of small hypersphere