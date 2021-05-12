/*==============================================================================
Project: Bulk Synchronous Farm (BSF)
Theme: BSF Skeleton
Module: Problem-bsfCode.cpp (Problem-dependent Code)
Prefix: PC
Author: Leonid B. Sokolinsky
This source code is a part of BSF Skeleton (https://github.com/leonid-sokolinsky/BSF-skeleton)
==============================================================================*/
#include "Problem-Data.h"			// Problem Types 
#include "Problem-Forwards.h"		// Problem Function Forwards
#include "Problem-bsfParameters.h"	// BSF-skeleton parameters
#include "BSF-SkeletonVariables.h"	// Skeleton Variables
using namespace std;

//----------------------- Predefined problem-dependent functions -----------------
void PC_bsf_Init(bool* success) {
	srand((unsigned)time(NULL) * (BSF_sv_mpiRank + 10));

	for (int j = 0; j < PP_N; j++)
		PD_center[j] = PP_THETA;

	for (int j = 0; j < PP_N; j++) {
		PD_c[j] = (PT_float_T)(PP_N - j) * PP_RHO;
		PD_centerObjectF += PD_c[j] * PP_THETA;
	}

	for (int i = 0; i < PP_N; i++) {
		for (int j = 0; j < PP_N; j++)
			PD_A[i][j] = 0;
		PD_A[i][i] = 1;
		PD_b[i] = PP_ALPHA;
	}

	for (int j = 0; j < PP_N; j++)
		PD_A[PP_N][j] = 1;
	PD_b[PP_N] = PP_ALPHA * (PP_N - 1) + PP_ALPHA / 2;

	for (int i = PP_N + 1; i < 2 * PP_N + 1; i++) {
		for (int j = 0; j < PP_N; j++)
			PD_A[i][j] = 0;
		PD_A[i][i - PP_N - 1] = -1;
		PD_b[i] = 0;
	}

	for (int i = 0; i < 2 * PP_N + 1; i++)
		PD_aNorm[i] = sqrt(Vector_NormSquare(PD_A[i]));
}

void PC_bsf_SetListSize(int* listSize) {
	*listSize = BSF_sv_numOfWorkers;
}

void PC_bsf_CopyParameter(PT_bsf_parameter_T parameterIn, PT_bsf_parameter_T* parameterOutP) {

}

void PC_bsf_MapF(PT_bsf_mapElem_T* mapElem, PT_bsf_reduceElem_T* reduceElem, int* success) {	// For Job 0
	PT_float_T distToCenter;
	PT_float_T aNormSquare;
	PT_vector_T centerProjection;
	PT_float_T aDotProductCenter;
	PT_float_T centerProjectionObjectiveF;

	reduceElem->failuresType1 = 0;
	reduceElem->failuresType2 = 0;
	reduceElem->failuresType3 = 0;

	do {
		RndFloatVector(reduceElem->a);
		if (reduceElem->a[0] == 0) reduceElem->a[0] += (PT_float_T)0.1;
		reduceElem->b = RndFloatValue(PP_B_MAX);

		aNormSquare = Vector_NormSquare(reduceElem->a);
		reduceElem->aNorm = sqrt(aNormSquare);
		aDotProductCenter = Vector_DotProduct(PD_center, reduceElem->a);
		distToCenter = fabs(aDotProductCenter - reduceElem->b) / reduceElem->aNorm;
		if (distToCenter > PP_THETA || distToCenter < PP_RHO) {
			reduceElem->failuresType1++;
			continue;
		}

		ProjectionOnHiperplane(PD_center, reduceElem->a, aNormSquare, aDotProductCenter, reduceElem->b, centerProjection);
		centerProjectionObjectiveF = Vector_DotProduct(PD_c, centerProjection);
		if (PD_centerObjectF > centerProjectionObjectiveF) {
			reduceElem->failuresType2++;
			continue;
		}

		if (!PointIn(PD_center, reduceElem->a, reduceElem->b)) {
			for (int j = 0; j < PP_N; j++)
				reduceElem->a[j] = -reduceElem->a[j];
			reduceElem->b = -reduceElem->b;
		}
			
		bool like = false;
		for (int i = 0; i < PP_N + 1; i++)
			if (like = Like(reduceElem->a, reduceElem->b, reduceElem->aNorm, PD_A[i], PD_b[i], PD_aNorm[i]))
				break;

		if (like) {
			reduceElem->failuresType3++;
			continue;
		}

		break;
	} while (true);
}

void PC_bsf_MapF_1(PT_bsf_mapElem_T* mapElem, PT_bsf_reduceElem_T_1* reduceElem, int* success) {// For Job 1
	// Optional filling. Do not delete!
}

void PC_bsf_MapF_2(PT_bsf_mapElem_T* mapElem, PT_bsf_reduceElem_T_2* reduceElem, int* success) {// For Job 2
	// Optional filling. Do not delete!
}

void PC_bsf_MapF_3(PT_bsf_mapElem_T* mapElem, PT_bsf_reduceElem_T_3* reduceElem, int* success) {// For Job 3
	// Optional filling. Do not delete!
}

void PC_bsf_ReduceF(PT_bsf_reduceElem_T* x, PT_bsf_reduceElem_T* y, PT_bsf_reduceElem_T* z) {			// For Job 0
	// z = x (+) y
	z->failuresType1 = x->failuresType1 + y->failuresType1;
	z->failuresType2 = x->failuresType2 + y->failuresType2;
	z->failuresType3 = x->failuresType3 + y->failuresType3;
}

void PC_bsf_ReduceF_1(PT_bsf_reduceElem_T_1* x, PT_bsf_reduceElem_T_1* y, PT_bsf_reduceElem_T_1* z) {	// For Job 1
	// Optional filling. Do not delete!
}

void PC_bsf_ReduceF_2(PT_bsf_reduceElem_T_2* x, PT_bsf_reduceElem_T_2* y, PT_bsf_reduceElem_T_2* z) {	// For Job 2
	// Optional filling. Do not delete!
}

void PC_bsf_ReduceF_3(PT_bsf_reduceElem_T_3* x, PT_bsf_reduceElem_T_3* y, PT_bsf_reduceElem_T_3* z) {	// For Job 3
	// optional filling
}

void PC_bsf_ProcessResults(		// For Job 0
	PT_bsf_reduceElem_T* reduceResult,
	int reduceCounter, 
	PT_bsf_parameter_T* parameter, 
	int* nextJob,
	bool* exit 
) {
	bool like;
	struct extendedReduceElem_T {	// Extended element type of reduce list
		PT_bsf_reduceElem_T elem;	// Element of reduce list
		int reduceCounter;			// Reduce Counter
	};
	extendedReduceElem_T* extendedReduceElem;

	if (PD_k == PP_NUM_OF_RND_INEQUALITIES + 2 * PP_N + 1) {
		*exit = true;
		return;
	}

	PD_failuresType1 += reduceResult->failuresType1;
	PD_failuresType2 += reduceResult->failuresType2;
	PD_failuresType3 += reduceResult->failuresType3;
			
	extendedReduceElem = (extendedReduceElem_T*)reduceResult;

	/* debug *//*cout << "----------------\n";
	for (int w = 0; w < BSF_sv_numOfWorkers; w++) {
		cout << "w=" << w << ")\t";
		for (int j = 0; j < PP_N; j++) cout << setw(PP_SETW) << extendedReduceElem[w].elem.a[j] << "\t";
		cout << "<=\t" << setw(PP_SETW) << extendedReduceElem[w].elem.b << endl;
	}/* end debug */

	for (int w = 0; w < BSF_sv_numOfWorkers; w++) {

		like = false;

		for (int i = 2 * PP_N + 1; i < PD_k; i++) {
			if (like = Like(extendedReduceElem[w].elem.a, extendedReduceElem[w].elem.b, extendedReduceElem[w].elem.aNorm, PD_A[i], PD_b[i], PD_aNorm[i]))
				break;
		}

		if (like) {
			PD_failuresType3++;
			continue;
		}

		Vector_Copy(extendedReduceElem[w].elem.a, PD_A[PD_k]);
		PD_b[PD_k] = extendedReduceElem[w].elem.b;
		PD_aNorm[PD_k] = extendedReduceElem[w].elem.aNorm;
		PD_k++;

		if (PD_k == PP_NUM_OF_RND_INEQUALITIES + 2 * PP_N + 1) {
			*exit = true;
			return;
		}
	}
}

void PC_bsf_ProcessResults_1(	// For Job 1	
	PT_bsf_reduceElem_T_1* reduceResult,
	int reduceCounter, 
	PT_bsf_parameter_T* parameter, 
	int* nextJob,
	bool* exit 
) {
	// Optional filling. Do not delete!
}

void PC_bsf_ProcessResults_2(	// For Job 2
	PT_bsf_reduceElem_T_2* reduceResult,
	int reduceCounter, 
	PT_bsf_parameter_T* parameter, 
	int* nextJob,
	bool* exit 
	) {
	// Optional filling. Do not delete!
}

void PC_bsf_ProcessResults_3(	// For Job 3
	PT_bsf_reduceElem_T_3* reduceResult,
	int reduceCounter, 
	PT_bsf_parameter_T* parameter, 
	int* nextJob,
	bool* exit 
	) {
	// Optional filling. Do not delete!
}

void PC_bsf_JobDispatcher(
	PT_bsf_parameter_T* parameter, // Current Approximation
	int* job,
	bool* exit
) {
	// Optional filling. Do not delete!
}

void PC_bsf_ParametersOutput(PT_bsf_parameter_T parameter) {
	cout << "=================================================== Problem parameters ====================================================" << endl;
	cout << "Number of Workers: " << BSF_sv_numOfWorkers << endl;
#ifdef PP_BSF_OMP
#ifdef PP_BSF_NUM_THREADS
	cout << "Number of Threads: " << PP_BSF_NUM_THREADS << endl;
#else
	cout << "Number of Threads: " << omp_get_num_procs() << endl;
#endif // PP_BSF_NUM_THREADS
#else
	cout << "OpenMP is turned off!" << endl;
#endif // PP_BSF_OMP
	cout << "Dimension: n = " << PP_N << endl;
	cout << "Number of Random Inegualities: " << PP_NUM_OF_RND_INEQUALITIES << endl;
	cout << "Length of hypercube edge ALPHA = " << PP_ALPHA << endl;
	cout << "Radius of large hypersphere RHO = " << PP_THETA << endl;
	cout << "Radius of small hypersphere THETA = " << PP_RHO << endl;
	cout << "Maximal acceptable likeness of equations MAX_LIKE = " << PP_MAX_LIKE << endl;
	cout << "Minimal acceptable shift MIN_SHIFT = " << PP_MIN_SHIFT << endl;
#ifdef PP_MATRIX_OUTPUT
	cout << "------- Support inequalities -------" << endl;
	for (int i = 0; i < 2 * PP_N + 1; i++) {
		cout << i << ")";
		for (int j = 0; j < PP_N; j++)
			cout << setw(PP_SETW) << PD_A[i][j];
		cout << "\t<=" << setw(PP_SETW) << PD_b[i] << endl;
	}
#endif // PP_MATRIX_OUTPUT

	cout << "Objective Function:\t";
	for (int j = 0; j < PF_MIN(PP_OUTPUT_LIMIT, PP_N); j++) cout << setw(PP_SETW) << PD_c[j];
	cout << (PP_OUTPUT_LIMIT < PP_N ? "	..." : "") << endl;
}

void PC_bsf_IterOutput(PT_bsf_reduceElem_T* reduceResult, int reduceCounter, PT_bsf_parameter_T parameter,
	double elapsedTime, int jobCase) {	// For Job 0
	static int k = 2 * PP_N + 1;
	cout << "------------------ " << BSF_sv_iterCounter << " ------------------" << endl;

	if (PD_k > k) {
		cout << PD_k - 1 << ")\t";
		for (int j = 0; j < PF_MIN(PP_OUTPUT_LIMIT, PP_N); j++) cout << setw(PP_SETW) << PD_A[PD_k - 1][j] << "\t";
		cout << (PP_OUTPUT_LIMIT < PP_N ? "	..." : "") << "<=\t" << setw(PP_SETW) << PD_b[PD_k - 1] << endl;
		k = PD_k;
	}
	cout << "Failures 'Not between' = " << PD_failuresType1 << endl;
	cout << "Failures 'Obtuse angle to objective' = " << PD_failuresType2 << endl;
	cout << "Failures 'Similar' = " << PD_failuresType3 << endl;
}

void PC_bsf_IterOutput_1(PT_bsf_reduceElem_T_1* reduceResult, int reduceCounter, PT_bsf_parameter_T parameter,
	double elapsedTime, int jobCase) {	// For Job 1
	cout << "------------------ " << BSF_sv_iterCounter << " ------------------" << endl;
	// Optional filling. Do not delete!

}

void PC_bsf_IterOutput_2(PT_bsf_reduceElem_T_2* reduceResult, int reduceCounter, PT_bsf_parameter_T parameter,
	double elapsedTime, int jobCase) {	// For Job 2
	cout << "------------------ " << BSF_sv_iterCounter << " ------------------" << endl;
	// Optional filling. Do not delete!

}

void PC_bsf_IterOutput_3(PT_bsf_reduceElem_T_3* reduceResult, int reduceCounter, PT_bsf_parameter_T parameter,
	double elapsedTime, int jobCase) {	// For Job 3
	cout << "------------------ " << BSF_sv_iterCounter << " ------------------" << endl;
	// Optional filling. Do not delete!

}

void PC_bsf_ProblemOutput(PT_bsf_reduceElem_T* reduceResult, int reduceCounter, PT_bsf_parameter_T parameter,
	double t) 
{
	cout << "=============================================" << endl;
	cout << "Time: " << t << endl;
	cout << "Iterations: " << BSF_sv_iterCounter << endl;
#ifdef PP_MATRIX_OUTPUT
	cout << "------- Random inequalities -------" << endl;
	for (int i = 2 * PP_N + 1; i < 2 * PP_N + 1 + PP_NUM_OF_RND_INEQUALITIES; i++) {
		cout << i << ")\t";
		for (int j = 0; j < PF_MIN(PP_OUTPUT_LIMIT, PP_N); j++) cout << setw(PP_SETW) << PD_A[i][j] << "\t";
		cout << (PP_OUTPUT_LIMIT < PP_N ? "	..." : "") << "<=\t" << setw(PP_SETW) << PD_b[i] << endl;
	}
	cout << "-----------------------------------" << endl;
#endif // PP_MATRIX_OUTPUT
	cout << "Failures 'Not between' = " << PD_failuresType1 << endl;
	cout << "Failures 'Obtuse angle to objective' = " << PD_failuresType2 << endl;
	cout << "Failures 'Similar' = " << PD_failuresType3 << endl;
#ifdef PP_FILE_OUTPUT
	PD_fileName = PP_PATH;
	PD_fileName += PP_LPP_FILE;
	const char* fileName = PD_fileName.c_str();
	FILE* stream;
	cout << "-----------------------------------" << endl;
	stream = fopen(fileName, "w");
	if (stream == NULL) {
		cout << "Failure of opening file " << fileName << "!\n";
		return;
	}
	fprintf(stream, "%d\t%d\n", PP_M, PP_N);

	for (int i = 0; i < PP_M; i++) {
		for (int j = 0; j < PP_N; j++)
			fprintf(stream, "%.2f\t", PD_A[i][j]);
		fprintf(stream, "%.2f\n", PD_b[i]);
	}
	for (int j = 0; j < PP_N; j++)
		fprintf(stream, "%.2f\t", PD_c[j]);

	fclose(stream);
	cout << "LPP is saved into file '" << fileName << "'." << endl;
	cout << "-----------------------------------" << endl;
#endif // PP_FILE_OUTPUT
}

void PC_bsf_ProblemOutput_1(PT_bsf_reduceElem_T_1* reduceResult, int reduceCounter, PT_bsf_parameter_T parameter,
	double t) {	// For Job 1
	// Optional filling. Do not delete!
}

void PC_bsf_ProblemOutput_2(PT_bsf_reduceElem_T_2* reduceResult, int reduceCounter, PT_bsf_parameter_T parameter,
	double t) {	// For Job 2
	// Optional filling. Do not delete!
}

void PC_bsf_ProblemOutput_3(PT_bsf_reduceElem_T_3* reduceResult, int reduceCounter, PT_bsf_parameter_T parameter,
	double t) {	// For Job 3
	// Optional filling. Do not delete!
}

void PC_bsf_SetInitParameter(PT_bsf_parameter_T* parameter) {

}

void PC_bsf_SetMapListElem(PT_bsf_mapElem_T* elem, int i) {

}

//----------------------- Assigning Values to BSF-skeleton Variables (Do not modify!) -----------------------
void PC_bsfAssignAddressOffset(int value) { BSF_sv_addressOffset = value; }
void PC_bsfAssignIterCounter(int value) { BSF_sv_iterCounter = value; }
void PC_bsfAssignJobCase(int value) { BSF_sv_jobCase = value; }
void PC_bsfAssignMpiMaster(int value) { BSF_sv_mpiMaster = value; }
void PC_bsfAssignMpiRank(int value) { BSF_sv_mpiRank = value; }
void PC_bsfAssignNumberInSublist(int value) { BSF_sv_numberInSublist = value; }
void PC_bsfAssignNumOfWorkers(int value) { BSF_sv_numOfWorkers = value; }
void PC_bsfAssignParameter(PT_bsf_parameter_T parameter) { PC_bsf_CopyParameter(parameter, &BSF_sv_parameter); }
void PC_bsfAssignSublistLength(int value) { BSF_sv_sublistLength = value; }

//----------------------------- User functions -----------------------------
inline PT_float_T Vector_DotProduct(PT_vector_T x, PT_vector_T y) {
	PT_float_T s = 0;
	for (int j = 0; j < PP_N; j++)
		s += x[j] * y[j];
	return s;
}

inline PT_float_T Vector_NormSquare(PT_vector_T x) {
	PT_float_T s = 0;

	for (int j = 0; j < PP_N; j++)
		s += x[j] * x[j];
	return s;
}

inline void RndFloatVector(PT_vector_T vector) {
	for (int i = 0; i < PP_N; i++)
		vector[i] = RndFloatValue(PP_A_MAX);
}

inline PT_float_T RndFloatValue(PT_float_T rndMax) {
	return RndSign() * (((PT_float_T)rand() / ((PT_float_T)RAND_MAX + 1)) * rndMax);
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

inline bool Like(PT_vector_T a1, PT_float_T b1, PT_float_T a1Norm, PT_vector_T a2, PT_float_T b2, PT_float_T a2Norm) {
	PT_float_T like, shift;
	PT_vector_T e1, e2, e1_e2;

	Vector_MultiplyByNumber(a1, 1 / a1Norm, e1);
	Vector_MultiplyByNumber(a2, 1 / a2Norm, e2);

	Vector_Subtraction(e1, e2, e1_e2);
	like = sqrt(Vector_NormSquare(e1_e2));
	shift = fabs(b1 / a1Norm - b2 / a2Norm);
	if (like < PP_MAX_LIKE)
		if (shift < PP_MIN_SHIFT)
			return true;
	return false;
}

inline void ProjectionOnHiperplane(PT_vector_T x, PT_vector_T a, PT_float_T aNormSquare, PT_float_T aDotProductx, PT_float_T b, PT_vector_T projection) {
	PT_float_T fac = (aDotProductx - b) / aNormSquare;
	for (int j = 0; j < PP_N; j++)
		projection[j] = x[j] - fac * a[j];
}

inline void Vector_MultiplyByNumber(PT_vector_T x, PT_float_T r, PT_vector_T y) {  // y = r*x
	for (int j = 0; j < PP_N; j++) {
		y[j] = x[j] * r;
	}
}

inline void Vector_Subtraction(PT_vector_T x, PT_vector_T y, PT_vector_T z) {  // z = x - y
	for (int j = 0; j < PP_N; j++) {
		z[j] = x[j] - y[j];
	}
}

inline void Vector_Addition(PT_vector_T x, PT_vector_T y, PT_vector_T z) {  // z = x + y
	for (int j = 0; j < PP_N; j++) {
		z[j] = x[j] + y[j];
	}
}

inline void Vector_Copy(PT_vector_T fromPoint, PT_vector_T toPoint) { // toPoint = fromPoint
	for (int j = 0; j < PP_N; j++) {
		toPoint[j] = fromPoint[j];
	}
}