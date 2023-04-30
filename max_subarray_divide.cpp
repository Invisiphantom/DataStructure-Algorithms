/**
 * @file max_subarray_divide.cpp
 * @author Invisiphatom (ethancao16770@gmail.com)
 * @brief solve Max Subarray Problem with Divide and Conquer Algorithm following CLRS P40
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

int max_across_subarray(vector<int> _array, size_t left, size_t mid,
												size_t right) {
	int lmax = -10000, rmax = -10000, lsum = 0, rsum = 0;
	for (auto lIter = _array.begin() + mid; lIter >= _array.begin() + left;
			 lIter--) {
		lsum += *lIter;
		lmax = max(lsum, lmax);
	}
	for (auto rIter = _array.begin() + mid + 1; rIter <= _array.begin() + right;
			 rIter++) {
		rsum += *rIter;
		rmax = max(rsum, rmax);
	}
	return lmax + rmax;
}

int max_subarray(vector<int> _array, size_t left, size_t right) {
	if (left == right) return _array.at(left);
	size_t mid = (left + right) / 2;
	int lmax = max_subarray(_array, left, mid);
	int rmax = max_subarray(_array, mid + 1, right);
	int mmax = max_across_subarray(_array, left, mid, right);
	return max(max(lmax, rmax), mmax);
}

int main() {
	vector<int> a = {1, -1, 2, 3, -1};
	cout << max_subarray(a, 0, a.size() - 1) << endl;
	return 0;
}