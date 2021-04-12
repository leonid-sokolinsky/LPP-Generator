/*==============================================================================
Project: Bulk Synchronous Farm (BSF)
Theme: BSF Skeleton
Module: Problem-bsfParameters.h (BSF-skeleton parameters)
Prefix: PP_BSF
Author: Leonid B. Sokolinsky
This source code is a part of BSF Skeleton (https://github.com/leonid-sokolinsky/BSF-skeleton)
==============================================================================*/

//=========================== Skeleton Parameters =========================
#define PP_BSF_MAX_MPI_SIZE 500		// Defines the maximum possible number of MPI processes
#define PP_BSF_PRECISION 6			// Sets the decimal precision to be used to format floating-point values on output operations
#define PP_BSF_ITER_OUTPUT			// If it is defined then Iteration Output is performed
#define PP_BSF_TRACE_COUNT 50		// Each PP_BSF_TRACE_COUNT-th iteration to be outputted
#define PP_BSF_MAX_JOB_CASE 0		// Defines the maximum number of activities (jobs) in workflow minus 1
//--------------------------- OpenMP Parameters ---------------------------
#define PP_BSF_OMP					// If PP_BSF_OMP is defined then OpenMP is turned on for Map Step
#define PP_BSF_NUM_THREADS 12		// If PP_BSF_NUM_THREADS is udefined then all accessable threads are used