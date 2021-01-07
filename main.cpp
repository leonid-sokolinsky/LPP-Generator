/*==============================================================================
Project: LiFe
Theme: LPP Generator
Module: Driver
Author: Leonid B. Sokolinsky
==============================================================================*/
#include <iostream>
#include <iomanip>
#include "ISG-API.h"
using namespace std;
typedef double PT_float_T;

int main() {
	static PT_matrix_T A;
	static PT_column_T b;
	static PT_vector_T c;

	cout << setprecision(4);

	ISG_Init();
	ISG_GenerateLPP(A, b, c);

	cout << "--- Inequality system: ---\n";
	for (int i = 0; i < ISG_M; i++) {
		cout << i + 1 <<":\t";
		for (int j = 0; j < ISG_N; j++)
			cout << A[i][j] << "\t";
		cout << "<= " << b[i] << "\n";
	}
	cout << "--- Objective function: ---\n";
	for (int j = 0; j < ISG_N; j++)
		cout << c[j] << "\t";
	cout << "\n";
}