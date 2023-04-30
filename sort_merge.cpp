/**
 * @file sort_merge.cpp
 * @author Invisiphatom (ethancao16770@gmail.com)
 * @brief a merge sort code following CLRS P18
 * @version 0.1
 * @date 2023-04-05
 * 
 * @copyright Copyright (c) 2023 Invisiphatom
 * All Rights Reserved.
 * 
 */
#include <algorithm>
#include <deque>
#include <functional>
#include <iostream>
#include <vector>
using namespace std;

template <class T>
void merge(vector<T>& _array, size_t left, size_t right, size_t mid) {
	auto _larray = deque<T>(_array.begin() + left, _array.begin() + mid + 1);
	auto _rarray = deque<T>(_array.begin() + mid + 1, _array.begin() + right + 1);
	for (auto Iter = _array.begin() + left; Iter <= _array.begin() + right;
			 Iter++) {
		if (_rarray.empty() == true) {
			*Iter = _larray.front();
			_larray.pop_front();
		} else if (_larray.empty() == true) {
			*Iter = _rarray.front();
			_rarray.pop_front();
		} else {
			if (_larray.front() > _rarray.front()) {
				*Iter = _larray.front();
				_larray.pop_front();
			} else {
				*Iter = _rarray.front();
				_rarray.pop_front();
			}
		}
	}
}

template <class T>
void merge_sort(vector<T>& _array, size_t left, size_t right) {
	if (left != right) {
		size_t mid = size_t((left + right) / 2);
		merge_sort(_array, left, mid);
		merge_sort(_array, mid + 1, right);
		merge(_array, left, right, mid);
		// inplace_merge(_array.begin() + left, _array.begin() + mid + 1,
		// 							_array.begin() + right + 1, greater<T>());
	}
}

int main() {
	vector<long double> a = {5, 2, 4, 6, 1, 3};
	vector<string> b = {"a", "w", "h", "j", "m", "a", "c"};

	merge_sort(a, 0, a.size() - 1);
	for (auto x : a) cout << x << " ";
	cout << endl;

	merge_sort(b, 0, b.size() - 1);
	for (auto y : b) cout << y << " ";
	cout << endl;

	return 0;
}