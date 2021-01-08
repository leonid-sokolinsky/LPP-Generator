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
typedef double ISG_float_T;

int main() {
	static ISG_matrix_T A;
	static ISG_column_T b;
	static ISG_vector_T c;

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

	errno_t err;
	err = ISG_SaveLPP(A, b, c, "C:/TEMP/lpp.txt");
	if (err != 0)
		cout << "Write failure! Error number: " << err << endl;
	else
		cout << "LPP is saved successfully!" << endl;
}