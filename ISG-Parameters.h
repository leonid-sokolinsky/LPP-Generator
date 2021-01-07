/*==============================================================================
Project: LiFe
Theme: LPP Generator
Module: Application programming interface
Prefix: ISG
Author: Leonid B. Sokolinsky
==============================================================================*/
#define ISG_N 2											// Space dimension	
#define ISG_NUM_OF_RND_INEQUALITIES 10					// Number of random inequalities
#define ISG_M (2*ISG_N + ISG_NUM_OF_RND_INEQUALITIES)	// Total number of inequalities
#define ISG_ALPHA 20									// Length of hypercube edge
#define ISG_RHO (ISG_ALPHA/2)							// Radius of large hypersphere
#define ISG_THETA (ISG_RHO/2)							// Radius of small hypersphere