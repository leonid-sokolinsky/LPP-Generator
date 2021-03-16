/*==============================================================================
Project: LiFe
Theme: LPP Generator
Module: Problem-bsf-Forwards.h (Problem Function Forwards)
Author: Leonid B. Sokolinsky 
==============================================================================*/
#include "Problem-bsfTypes.h"	// Predefined BSF types
#include "Problem-Types.h"		// Problem Types
//====================== Problem Functions ===========================
bool		Like(PT_vector_T a1, PT_float_T b1, PT_float_T a1Norm, PT_vector_T a2, PT_float_T b2, PT_float_T a2Norm);
void		ProjectionOnHiperplane(PT_vector_T x, PT_vector_T a, PT_float_T aNormSquare, PT_float_T aDotProductx, PT_float_T b, PT_vector_T projection);
bool		PointIn(PT_vector_T x, PT_vector_T a, PT_float_T b);
PT_float_T	RndFloatValue(PT_float_T rndMax);
void		RndFloatVector(PT_vector_T vector);
int			RndSign();
void		Vector_Addition(PT_vector_T x, PT_vector_T y, PT_vector_T z);
void		Vector_Copy(PT_vector_T fromPoint, PT_vector_T toPoint);
PT_float_T	Vector_DotProduct(PT_vector_T x, PT_vector_T y);
void		Vector_MultiplyByNumber(PT_vector_T x, PT_float_T r, PT_vector_T y);
PT_float_T	Vector_NormSquare(PT_vector_T x);
void		Vector_Subtraction(PT_vector_T x, PT_vector_T y, PT_vector_T z);
//====================== Macros ================================
#define PF_MIN(x,y) (x<y?x:y)
#define PF_MAX(x,y) (x>y?x:y)