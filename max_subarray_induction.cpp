/**
 * @file max_subarray_induction.cpp
 * @author Invisiphatom (ethancao16770@gmail.com)
 * @brief solve Max Subarray Problem with Induction and Recursive Algorithm following CLRS P42 4.1-5
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

int max_across_subarray(vector<int> _array, size_t right) {
	int lmax = -10000, lsum = 0;
	for (auto lIter = _array.begin() + right; lIter >= _array.begin(); lIter--) {
		lsum += *lIter;
		lmax = max(lsum, lmax);
	}
	return lmax;
}

int max_subarray(vector<int> _array, size_t right) {
	if (right == 0) return _array.front();
	int former_max = max_subarray(_array, right - 1);
	int left_max = max_across_subarray(_array, right);
	return max(former_max, left_max);
}

int main() {
	vector<int> a = {1, -1, 2, 3, -1};
	cout << max_subarray(a, a.size() - 1) << endl;
	return 0;
}