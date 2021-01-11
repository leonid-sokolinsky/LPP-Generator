/*==============================================================================
Project: LiFe
Theme: LPP Generator
Module: Forwards of Static Function
Prefix: ISG
Author: Leonid B. Sokolinsky
==============================================================================*/
#include "ISG-Types.h"

void		GenA_i(ISG_float_T* a, int i);
ISG_float_T GenB_i(int i);
bool		Like(ISG_vector_T a1, ISG_float_T b1, ISG_float_T a1Norm, ISG_vector_T a2, ISG_float_T b2, ISG_float_T a2Norm);
void		MakeRndInequality(ISG_vector_T a, ISG_float_T* b, ISG_vector_T c, ISG_float_T* aNorm);
void		ProjectionOnHiperplane(ISG_vector_T x, ISG_vector_T a, ISG_float_T aNormSquare, ISG_float_T aDotProductx, ISG_float_T b, ISG_vector_T projection);
bool		PointIn(ISG_vector_T x, ISG_vector_T a, ISG_float_T b);
ISG_float_T	RndFloatValue(double rndMax);
void		RndFloatVector(ISG_vector_T vector);
int			RndSign();
double		Vector_DotProduct(ISG_vector_T x, ISG_vector_T y);
double		Vector_NormSquare(ISG_vector_T x);