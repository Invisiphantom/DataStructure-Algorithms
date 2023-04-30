/**
 * @file matrix_mult_strassen.cpp
 * @author Invisiphatom (ethancao16770@gmail.com)
 * @brief solve matrix multiplication with strassen following CLRS P45
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

Matrix operator+(Matrix _Amatrix, Matrix _Bmatrix) {
	int n = _Amatrix.size();
	Matrix _Rmatrix(n, vector<int>(n, 0));
	for (int i = 0; i < n; i++)
		for (int j = 0; j < n; j++)
			_Rmatrix[i][j] = _Amatrix[i][j] + _Bmatrix[i][j];
	return _Rmatrix;
}
Matrix operator-(Matrix _Amatrix, Matrix _Bmatrix) {
	int n = _Amatrix.size();
	Matrix _Rmatrix(n, vector<int>(n, 0));
	for (int i = 0; i < n; i++)
		for (int j = 0; j < n; j++)
			_Rmatrix[i][j] = _Amatrix[i][j] - _Bmatrix[i][j];
	return _Rmatrix;
}

Matrix slice_matrix(Matrix _matrix, int row, int col, int n) {
	Matrix _Rmatrix(n, vector<int>(n, 0));
	for (int i = 0; i < n; i++)
		for (int j = 0; j < n; j++) _Rmatrix[i][j] = _matrix[row + i][col + j];
	return _Rmatrix;
}

Matrix merge_matrix(Matrix _M11, Matrix _M12, Matrix _M21, Matrix _M22, int n) {
	Matrix _Rmatrix(n, vector<int>(n, 0));
	for (int i = 0; i < n / 2; i++)
		for (int j = 0; j < n / 2; j++) _Rmatrix[i][j] = _M11[i][j];
	for (int i = 0; i < n / 2; i++)
		for (int j = 0; j < n / 2; j++) _Rmatrix[i][n / 2 + j] = _M12[i][j];
	for (int i = 0; i < n / 2; i++)
		for (int j = 0; j < n / 2; j++) _Rmatrix[n / 2 + i][j] = _M21[i][j];
	for (int i = 0; i < n / 2; i++)
		for (int j = 0; j < n / 2; j++) _Rmatrix[n / 2 + i][n / 2 + j] = _M22[i][j];
	return _Rmatrix;
}

Matrix matrix_mult_strassen(Matrix _Amatrix, Matrix _Bmatrix, int n) {
	Matrix _Rmatrix(n, vector<int>(n, 0));
	if (n == 1) {
		_Rmatrix[0][0] = _Amatrix[0][0] * _Bmatrix[0][0];
		return _Rmatrix;
	}

	auto _A11 = slice_matrix(_Amatrix, 0, 0, n / 2);
	auto _A12 = slice_matrix(_Amatrix, 0, n / 2, n / 2);
	auto _A21 = slice_matrix(_Amatrix, n / 2, 0, n / 2);
	auto _A22 = slice_matrix(_Amatrix, n / 2, n / 2, n / 2);

	auto _B11 = slice_matrix(_Bmatrix, 0, 0, n / 2);
	auto _B12 = slice_matrix(_Bmatrix, 0, n / 2, n / 2);
	auto _B21 = slice_matrix(_Bmatrix, n / 2, 0, n / 2);
	auto _B22 = slice_matrix(_Bmatrix, n / 2, n / 2, n / 2);

	auto _S1 = _B12 - _B22;
	auto _S2 = _A11 + _A12;
	auto _S3 = _A21 + _A22;
	auto _S4 = _B21 - _B11;
	auto _S5 = _A11 + _A22;
	auto _S6 = _B11 + _B22;
	auto _S7 = _A12 - _A22;
	auto _S8 = _B21 + _B22;
	auto _S9 = _A11 - _A21;
	auto _S10 = _B11 + _B12;

	auto _P1 = matrix_mult_strassen(_A11, _S1, n / 2);
	auto _P2 = matrix_mult_strassen(_S2, _B22, n / 2);
	auto _P3 = matrix_mult_strassen(_S3, _B11, n / 2);
	auto _P4 = matrix_mult_strassen(_A22, _S4, n / 2);
	auto _P5 = matrix_mult_strassen(_S5, _S6, n / 2);
	auto _P6 = matrix_mult_strassen(_S7, _S8, n / 2);
	auto _P7 = matrix_mult_strassen(_S9, _S10, n / 2);

	auto _R11 = _P5 + _P4 - _P2 + _P6;
	auto _R12 = _P1 + _P2;
	auto _R21 = _P3 + _P4;
	auto _R22 = _P5 + _P1 - _P3 - _P7;

	_Rmatrix = merge_matrix(_R11, _R12, _R21, _R22, n);
	return _Rmatrix;
}

int main() {
	Matrix _Amatrix = {{2, 1}, {4, 3}}, _Bmatrix = {{1, 2}, {1, 0}};
	Matrix _Rmatrix = matrix_mult_strassen(_Amatrix, _Bmatrix, n);

	for (auto rIter : _Rmatrix) {
		for (auto cIter : rIter) cout << cIter << " ";
		cout << endl;
	}
	return 0;
}