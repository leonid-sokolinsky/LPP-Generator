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
	ISG_GenRndLPP(A, b, c);

	errno_t err;
	err = ISG_SaveLPP(A, b, c, ISG_FILE);
	if (err != 0)
		cout << "Write failure! Error number: " << err << endl;
	else
		cout << "LPP is saved into file '" << ISG_FILE << "'.\n" << endl;
}