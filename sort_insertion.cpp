/**
 * @file sort_insertion.cpp
 * @author Invisiphatom (ethancao16770@gmail.com)
 * @brief an insertion sort code following CLRS P10
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

template<class T>
void insertion_sort(vector<T>& _array) {
	for (size_t j = 1; j < _array.size(); j++) {
		auto key = _array[j];
		auto i = j - 1;
		while (i < _array.size() && key < _array[i]) {
			_array[i + 1] = _array[i];
			i--;
		}
		_array[i + 1] = key;
	}
}

int main() {
	vector<string> a = {"a", "b", "d", "c"};
	insertion_sort(a);
	for (auto x : a) cout << x << " ";
	cout << endl;
	return 0;
}