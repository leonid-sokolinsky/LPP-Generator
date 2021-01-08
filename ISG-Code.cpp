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
#define	DELTA_LIKE 1				// Acceptable likeness of equations
#define	DELTA_SHIFT (DELTA_LIKE*5)	// Acceptable quantity of shifting
#define	A_MAX (ISG_ALPHA*5)	// Maximal random value for A
#define	B_MAX (ISG_ALPHA*5000)				// Maximal random value for b
#define	C_MAX (ISG_THETA)		// Maximal random value for c
//------------------------------- Types -------------------------------
static PT_vector_T _hypercubeCenter;		// Center of hypercube
/* debug */static int failuresType1 = 0; /* end debug */
/* debug */static int failuresType2 = 0; /* end debug */

//------------------------------- External Functions --------------------
extern void ISG_Init() {
	for (int j = 0; j < ISG_N; j++)
		_hypercubeCenter[j] = ISG_RHO;
}

extern void ISG_GenerateLPP(PT_matrix_T A, PT_column_T b, PT_vector_T c) {
	double likeDif = DELTA_LIKE + 1;
	double likeSum = DELTA_LIKE + 1;
	double shiftDif = DELTA_SHIFT + 1;
	double shiftSum = DELTA_SHIFT + 1;

	assert(ISG_N * ISG_M * ISG_ALPHA * ISG_RHO * ISG_THETA * _hypercubeCenter[0] != 0);

	for (int i = 0; i < ISG_NUM_OF_RND_INEQUALITIES; i++) {
		int bad = 0;
		do {
			MakeRndInequality(A[i], &b[i]);
			for (int k = i - 1; k > -1; k--) {
				likeSum = LikeSum(A[i], A[k]);
				shiftSum = fabs(b[i] / A[i][0] + b[k] / A[k][0]);
				if (likeSum < DELTA_LIKE && shiftSum < DELTA_SHIFT) {
					/* debug */ bad++; /* end debug */
					//* debug */ cout << "likeSum = " << likeSum << "\tshiftSum =" << shiftSum << endl; /* end debug */
					//* debug */ cout << k + 1 << ": "; for (int j = 0; j < ISG_N; j++)	cout << A[k][j] << "\t"; cout << "<=\t" << b[k] << "\n"; /* end debug */
					//* debug */ cout << i + 1 << ": "; for (int j = 0; j < ISG_N; j++)	cout << A[i][j] << "\t"; cout << "<=\t" << b[i] << "\n"; /* end debug */
					//* debug */ cout << "------------------------\n";
					break;
				}
				likeDif = LikeDif(A[i],A[k]);
				shiftDif = fabs(b[i] / A[i][0] - b[k] / A[k][0]);
				if (likeDif < DELTA_LIKE && shiftDif < DELTA_SHIFT) {
					/* debug */ bad++; /* end debug */
					//* debug */ cout << "likeDif = " << likeDif << "\tshiftDif =" << shiftDif << endl;
					//* debug */ cout << k+1 << ": "; for (int j = 0; j < ISG_N; j++)	cout << A[k][j] << "\t"; cout << "<=\t" << b[k] << "\n";
					//* debug */ cout << i+1 << ": "; for (int j = 0; j < ISG_N; j++)	cout << A[i][j] << "\t"; cout << "<=\t" << b[i] << "\n";
					//* debug */ cout << "------------------------\n";
					break;
				}
			}
		} while ((likeDif < DELTA_LIKE && shiftDif < DELTA_SHIFT) || (likeSum < DELTA_LIKE && shiftSum < DELTA_SHIFT));

		/* debug */ if (bad > 0) failuresType2++; /* end debug */
		if (!PointIn(_hypercubeCenter, A[i], b[i])) {
			for (int j = 0; j < ISG_N; j++)
				A[i][j] = -A[i][j];
			b[i] = -b[i];
		}
	}

	for (int i = ISG_NUM_OF_RND_INEQUALITIES; i < ISG_NUM_OF_RND_INEQUALITIES + ISG_N; i++) {
		for (int j = 0; j < ISG_N; j++)
			A[i][j] = 0;
		A[i][i - ISG_NUM_OF_RND_INEQUALITIES] = -1;
		b[i] = 0;
	}

	for (int i = ISG_NUM_OF_RND_INEQUALITIES + ISG_N; i < ISG_M; i++) {
		for (int j = 0; j < ISG_N; j++)
			A[i][j] = 0;
		A[i][i - ISG_NUM_OF_RND_INEQUALITIES - ISG_N] = 1;
		b[i] = ISG_ALPHA;
	}

	for (int j = 0; j < ISG_N; j++)
		c[j] = ((double)rand() / (RAND_MAX + 1)) * C_MAX;
	/* debug */ cout << "Failures 'Not between' = " << failuresType1 << endl;  /* end debug */
	/* debug */ cout << "Failures 'Similar' = " << failuresType2 << endl;  /* end debug */
}

extern errno_t ISG_SaveLPP(PT_matrix_T A, PT_column_T b, PT_vector_T c, const char* filename) {
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
static void MakeRndInequality(PT_vector_T a, PT_float_T* b) {
	double dist;
	do {
		RndFloatVector(a);
		if(a[0] == 0)
			a[0] += 0.1;
		*b = RndFloatValue(B_MAX);
		dist = DistanceFromPointToHyperplane(_hypercubeCenter, a, *b);
		if (dist < ISG_RHO && dist > ISG_THETA)
			break;
		/* debug */ failuresType1++; /* end debug */
	} while (true);
}

inline double DistanceFromPointToHyperplane(PT_vector_T point, PT_vector_T a, PT_float_T b) {
	return fabs(Vector_DotProduct(point, a) - b) / sqrt(Vector_NormSquare(a));
}

static double Vector_DotProduct(PT_vector_T x, PT_vector_T y) {
	double s = 0;
	for (int j = 0; j < ISG_N; j++)
		s += x[j] * y[j];
	return s;
}

static double Vector_NormSquare(PT_vector_T x) {
	double s = 0;

	for (int j = 0; j < ISG_N; j++)
		s += x[j] * x[j];
	return s;
}

static void RndFloatVector(PT_vector_T vector) {
	for (int i = 0; i < ISG_N; i++)
		vector[i] = RndFloatValue(A_MAX);
}

inline PT_float_T RndFloatValue(double rndMax) {
	return RndSign() * (((double)rand() / (RAND_MAX + 1)) * rndMax);
}

inline int RndSign() {
	int res = rand() % 2;
	if (res == 0)
		res = -1;
	return res;
}

inline bool PointIn(PT_vector_T x, PT_vector_T a, PT_float_T b) { // If the point belonges to the Halfspace <a,x> <= b
	if (Vector_DotProduct(a, x) > b)
		return false;
	else
		return true;
}

static double LikeDif(PT_vector_T a1, PT_vector_T a2) {
	double s = 0;

	for (int j = 1; j < ISG_N; j++)
		s += fabs(a1[j] / a1[0] - a2[j] / a2[0]);
	//s /= ISG_N - 1;
	return s;
}

static double LikeSum(PT_vector_T a1, PT_vector_T a2) {
	double s = 0;

	for (int j = 1; j < ISG_N; j++)
		s += fabs(a1[j] / a1[0] + a2[j] / a2[0]);
	//s /= ISG_N - 1;
	return s;
}