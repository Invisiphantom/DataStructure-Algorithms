/**
 * @file matrix_mult_recur.cpp
 * @author Invisiphatom (ethancao16770@gmail.com)
 * @brief solve matrix multiplication with recurrence following CLRS P44
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
Matrix _Rmatrix(n, vector<int>(n, 0));
void matrix_mult_recur(Matrix _Amatrix, Matrix _Bmatrix, size_t Arow,
											 size_t Acol, size_t Brow, size_t Bcol, size_t n) {
	if (n == 1) {
		_Rmatrix[Arow][Bcol] += _Amatrix[Arow][Acol] * _Bmatrix[Brow][Bcol];
		return;
	}
	int Arow2 = Arow + n / 2, Acol2 = Acol + n / 2;
	int Brow2 = Brow + n / 2, Bcol2 = Bcol + n / 2;

	matrix_mult_recur(_Amatrix, _Bmatrix, Arow, Acol, Brow, Bcol, n / 2);
	matrix_mult_recur(_Amatrix, _Bmatrix, Arow, Acol2, Brow2, Bcol, n / 2);

	matrix_mult_recur(_Amatrix, _Bmatrix, Arow, Acol, Brow, Bcol2, n / 2);
	matrix_mult_recur(_Amatrix, _Bmatrix, Arow, Acol2, Brow2, Bcol2, n / 2);

	matrix_mult_recur(_Amatrix, _Bmatrix, Arow2, Acol, Brow, Bcol, n / 2);
	matrix_mult_recur(_Amatrix, _Bmatrix, Arow2, Acol2, Brow2, Bcol, n / 2);

	matrix_mult_recur(_Amatrix, _Bmatrix, Arow2, Acol, Brow, Bcol2, n / 2);
	matrix_mult_recur(_Amatrix, _Bmatrix, Arow2, Acol2, Brow2, Bcol2, n / 2);
}

int main() {
	Matrix _Amatrix = {{2, 1}, {4, 3}}, _Bmatrix = {{1, 2}, {1, 0}};
	matrix_mult_recur(_Amatrix, _Bmatrix, 0, 0, 0, 0, n);
	for (auto rIter : _Rmatrix) {
		for (auto cIter : rIter) cout << cIter << " ";
		cout << endl;
	}
}
