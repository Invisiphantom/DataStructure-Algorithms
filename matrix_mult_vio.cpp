/**
 * @file matrix_mult_vio.cpp
 * @author Invisiphatom (ethancao16770@gmail.com)
 * @brief solve matrix multiplication with violence following CLRS P43
 * @version 0.1
 * @date 2023-04-05
 *
 * @copyright Copyright (c) 2023 Invisiphatom
 * All Rights Reserved.
 *
 */
#include <iostream>
#include <vector>

using namespace std;

static const int n = 2;
using Matrix = vector<vector<int>>;

auto matrix_mult(Matrix _Amatrix, Matrix _Bmatrix, int n) {
	Matrix _Rmatrix(n, vector<int>(n, 0));
	for (int i = 0; i < n; i++)
		for (int j = 0; j < n; j++)
			for (int k = 0; k < n; k++)
				_Rmatrix[i][j] += _Amatrix[i][k] * _Bmatrix[k][j];
	return _Rmatrix;
}

int main() {
	Matrix _Amatrix = {{2, 1}, {4, 3}}, _Bmatrix = {{1, 2}, {1, 0}};
	Matrix _Rmatrix = matrix_mult(_Amatrix, _Bmatrix, n);

	for (auto rIter : _Rmatrix) {
		for (auto cIter : rIter) cout << cIter << " ";
		cout << endl;
	}
	return 0;
}