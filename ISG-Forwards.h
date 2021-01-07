/*==============================================================================
Project: LiFe
Theme: LPP Generator
Module: Forwards of Ststic Function
Prefix: ISG
Author: Leonid B. Sokolinsky
==============================================================================*/
#include "ISG-Types.h"

double		LikeDif(PT_vector_T a1, PT_vector_T a2);
double		DistanceFromPointToHyperplane(PT_vector_T point, PT_vector_T a, PT_float_T b);
double		LikeDif(PT_vector_T a1, PT_vector_T a2);
double		LikeSum(PT_vector_T a1, PT_vector_T a2);
void		MakeRndInequality(PT_vector_T a, PT_float_T *b);
bool		PointIn(PT_vector_T x, PT_vector_T a, PT_float_T b);
PT_float_T	RndFloatValue(double rndMax);
void		RndFloatVector(PT_vector_T vector);
int			RndSign();
double		Vector_DotProduct(PT_vector_T x, PT_vector_T y);
double		Vector_NormSquare(PT_vector_T x);