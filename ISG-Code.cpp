/*==============================================================================
Project: LiFe
Theme: LPP Generator
Module: Generator of Random Feasible Inequality Systems
Prefix: ISG
Author: Leonid B. Sokolinsky
==============================================================================*/
#include "ISG-Include.h"
#include "ISG-Forwards.h"
#include "ISG-Parameters.h"
using namespace std;

//------------------------------- Parameters -------------------------------
#define	A_MAX (ISG_ALPHA*5)		// Maximal random value for A
#define	B_MAX (ISG_ALPHA*50)	// Maximal random value for b
#define	C_MAX (ISG_THETA)		// Maximal random value for c
//------------------------------- Types -------------------------------
static ISG_vector_T _center;		// Center of hypercube
static ISG_float_T _centerObjectF;	// Value of object function in the center of hypercube
static ISG_column_T _aNorm;
/* debug */static unsigned _failuresType1 = 0; /* end debug */
/* debug */static unsigned _failuresType2 = 0; /* end debug */

//------------------------------- External Functions --------------------
extern void ISG_Init() {
	srand((unsigned)time(NULL));

	for (int j = 0; j < ISG_N; j++)
		_center[j] = ISG_RHO;
}

extern void ISG_GenRndLPP(ISG_matrix_T A, ISG_column_T b, ISG_vector_T c) {
	assert(ISG_N * ISG_M * ISG_ALPHA * ISG_RHO * ISG_THETA * _center[0] != 0);

	for (int j = 0; j < ISG_N; j++) {
		c[j] = (ISG_N - j) * C_MAX;
		_centerObjectF += c[j] * ISG_RHO;
	}

	for (int i = 0; i < ISG_NUM_OF_NATURAL_INEQUALITIES; i++) {
		unsigned bad;
		bool like;

		bad = 0;
		do {
			MakeRndInequality(A[i], &b[i], c, &_aNorm[i]);
			like = false;
			for (int k = i - 1; k > -1; k--) {
				if (like = Like(A[i], b[i], _aNorm[i], A[k], b[k], _aNorm[k])) {
					/* debug */ bad++; /* end debug */
					//* debug */ cout << k + 1 << ": "; for (int j = 0; j < ISG_N; j++)	cout << A[k][j] << "\t"; cout << "<=\t" << b[k] << "\n"; /* end debug */
					//* debug */ cout << i + 1 << ": "; for (int j = 0; j < ISG_N; j++)	cout << A[i][j] << "\t"; cout << "<=\t" << b[i] << "\n"; /* end debug */
					//* debug */ cout << "------------------------\n";
					break;
				}
			}
		} while (like);

		/* debug */ if (bad > 0) _failuresType2++; /* end debug */
		if (!PointIn(_center, A[i], b[i])) {
			for (int j = 0; j < ISG_N; j++)
				A[i][j] = -A[i][j];
			b[i] = -b[i];
		}
	}

	for (int i = ISG_NUM_OF_NATURAL_INEQUALITIES; i < ISG_NUM_OF_NATURAL_INEQUALITIES + ISG_N; i++) {
		for (int j = 0; j < ISG_N; j++)
			A[i][j] = 0;
		A[i][i - ISG_NUM_OF_NATURAL_INEQUALITIES] = -1;
		b[i] = 0;
	}

	for (int i = ISG_NUM_OF_NATURAL_INEQUALITIES + ISG_N; i < ISG_M - 1; i++) {
		for (int j = 0; j < ISG_N; j++)
			A[i][j] = 0;
		A[i][i - ISG_NUM_OF_NATURAL_INEQUALITIES - ISG_N] = 1;
		b[i] = ISG_ALPHA;
	}

	for (int j = 0; j < ISG_N; j++)
		A[ISG_M - 1][j] = 1;
	
	b[ISG_M - 1] = ISG_ALPHA* (ISG_N - 1) + ISG_ALPHA / 2;


	/* debug */ cout << "Failures 'Not between' = " << _failuresType1 << endl;  /* end debug */
	/* debug */ cout << "Failures 'Similar' = " << _failuresType2 << endl;  /* end debug */
}

extern void ISG_GenMdlLPP(ISG_matrix_T A, ISG_column_T b, ISG_vector_T c) {
	assert(ISG_NUM_OF_NATURAL_INEQUALITIES == 0);
	/* debug */ cout << "m = " << ISG_M << "\t n = " << ISG_N << endl;

	for (int i = 0; i < ISG_M; i++) {
		ISG_vector_T a;

		GenA_i(a, i);
		for (int j = 0; j < ISG_N; j++)
			A[i][j] = a[j];
		b[i] = GenB_i(i);
	}
	// Generating Objective Function Coefficients
	for (int j = 0; j < ISG_N; j++)
		c[j] = (ISG_N - j) * C_MAX;
}

extern errno_t ISG_SaveLPP(ISG_matrix_T A, ISG_column_T b, ISG_vector_T c, const char* filename) {
	FILE* stream;
	errno_t err;

	err = fopen_s(&stream,filename, "w");
	if (err != 0)
		return err;

	fprintf_s(stream, "%d\t%d\n", ISG_M, ISG_N);

	for (int i = 0; i < ISG_M; i++) {
		for (int j = 0; j < ISG_N; j++)
			fprintf_s(stream, "%f\t", A[i][j]);
		fprintf_s(stream, "%f\n", b[i]);
	}
	for (int j = 0; j < ISG_N; j++)
		fprintf_s(stream, "%f\t", c[j]);

	err = fclose(stream);
	return err;
}

//------------------------------- Internal Functions --------------------
static void MakeRndInequality(ISG_vector_T a, ISG_float_T* b, ISG_vector_T c, ISG_float_T *aNorm) {
	ISG_float_T distToCenter;
	ISG_float_T aNormSquare;
	ISG_vector_T centerProjection;
	ISG_float_T aDotProductCenter;
	ISG_float_T centerProjectionObjectiveF;

	do {
		RndFloatVector(a);
		if(a[0] == 0) a[0] += 0.1;
		aNormSquare = Vector_NormSquare(a);
		*aNorm = sqrt(aNormSquare);
		aDotProductCenter = Vector_DotProduct(_center, a);
		*b = RndFloatValue(B_MAX);
		distToCenter = fabs(aDotProductCenter - *b) / *aNorm;
		if (distToCenter > ISG_RHO || distToCenter < ISG_THETA) continue;		
		 ProjectionOnHiperplane(_center, a, aNormSquare, aDotProductCenter, *b, centerProjection);
		 centerProjectionObjectiveF = Vector_DotProduct(c, centerProjection);
		 if (_centerObjectF > centerProjectionObjectiveF) {
			 /* debug */ _failuresType1++; /* end debug */
			 continue;
		 }
		break;
	} while (true);
}

static double Vector_DotProduct(ISG_vector_T x, ISG_vector_T y) {
	double s = 0;
	for (int j = 0; j < ISG_N; j++)
		s += x[j] * y[j];
	return s;
}

static double Vector_NormSquare(ISG_vector_T x) {
	double s = 0;

	for (int j = 0; j < ISG_N; j++)
		s += x[j] * x[j];
	return s;
}

static void RndFloatVector(ISG_vector_T vector) {
	for (int i = 0; i < ISG_N; i++)
		vector[i] = RndFloatValue(A_MAX);
}

inline ISG_float_T RndFloatValue(double rndMax) {
	return RndSign() * (((double)rand() / (RAND_MAX + 1)) * rndMax);
}

inline int RndSign() {
	int res = rand() % 2;
	if (res == 0)
		res = -1;
	return res;
}

inline bool PointIn(ISG_vector_T x, ISG_vector_T a, ISG_float_T b) { // If the point belonges to the Halfspace <a,x> <= b
	if (Vector_DotProduct(a, x) > b)
		return false;
	else
		return true;
}

static bool Like(ISG_vector_T a1, ISG_float_T b1, ISG_float_T a1Norm, ISG_vector_T a2, ISG_float_T b2, ISG_float_T a2Norm) {
	double like, shift;
	
	like = 0;
	for (int j = 0; j < ISG_N; j++) 
		like += fabs(a1[j] / a1Norm - a2[j] / a2Norm);
	shift = fabs(b1 / a1Norm - b2 / a2Norm);
	if (like < ISG_MAX_LIKE)
		if (shift < ISG_MIN_SHIFT)
			return true;

	like = 0;
	for (int j = 0; j < ISG_N; j++)
		like += fabs(a1[j] / a1Norm + a2[j] / a2Norm);
	shift = fabs(b1 / a1Norm + b2 / a2Norm);
	if (like < ISG_MAX_LIKE)
		if (shift < ISG_MIN_SHIFT)
			return true;

	return false;
}

static void GenA_i(ISG_float_T* a, int i) {

	if (i < ISG_N) {
		for (int j = 0; j < ISG_N; j++)
			a[j] = 0;
		a[i] = 1;
		return;
	}

	if (i < ISG_M - 1) {
		for (int j = 0; j < ISG_N; j++)
			a[j] = 0;
		a[i - ISG_N] = -1;
		return;
	}

	for (int j = 0; j < ISG_N; j++)
		a[j] = 1;
}

inline ISG_float_T GenB_i(int i) {
	if (i < ISG_N) return ISG_ALPHA;
	if (i < ISG_M - 1) return 0;
	return ISG_ALPHA * (ISG_N - 1) + ISG_ALPHA / 2;
}

inline void ProjectionOnHiperplane(ISG_vector_T x, ISG_vector_T a, ISG_float_T aNormSquare, ISG_float_T aDotProductx, ISG_float_T b, ISG_vector_T projection) {
	ISG_float_T fac = (aDotProductx - b) / aNormSquare;
	for (int j = 0; j < ISG_N; j++)
		projection[j] = x[j] - fac * a[j];
}