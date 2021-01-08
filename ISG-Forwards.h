/*==============================================================================
Project: LiFe
Theme: LPP Generator
Module: Forwards of Static Function
Prefix: ISG
Author: Leonid B. Sokolinsky
==============================================================================*/
#include "ISG-Types.h"

double		LikeDif(ISG_vector_T a1, ISG_vector_T a2);
double		DistanceFromPointToHyperplane(ISG_vector_T point, ISG_vector_T a, ISG_float_T b);
double		LikeDif(ISG_vector_T a1, ISG_vector_T a2);
double		LikeSum(ISG_vector_T a1, ISG_vector_T a2);
void		MakeRndInequality(ISG_vector_T a, ISG_float_T *b);
bool		PointIn(ISG_vector_T x, ISG_vector_T a, ISG_float_T b);
ISG_float_T	RndFloatValue(double rndMax);
void		RndFloatVector(ISG_vector_T vector);
int			RndSign();
double		Vector_DotProduct(ISG_vector_T x, ISG_vector_T y);
double		Vector_NormSquare(ISG_vector_T x);