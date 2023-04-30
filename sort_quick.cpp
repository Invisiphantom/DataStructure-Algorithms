#include <iostream>
#include <string>
#include <vector>

using namespace std;

template <class T>
void quick_sort(vector<T>& _array, const size_t begin, const size_t end) {
	auto key = _array[begin];
	auto left = begin, right = end;
	while (left < right) {
		while (_array[right] >= key && left < right) right--;
		_array[left] = _array[right];
		while (_array[left] <= key && left < right) left++;
		_array[right] = _array[left];
	}
	auto& middle = left;
	_array[middle] = key;
	if (begin < (middle - 1) && middle != 0)
		quick_sort(_array, begin, middle - 1);
	if (middle + 1 < end) quick_sort(_array, middle + 1, end);
}

int main() {
	vector<int> a = {5, 2, 4, 6, 1, 3};
	vector<string> b = {"a", "w", "h", "j", "m", "a", "c"};

	quick_sort(a, 0, a.size() - 1);
	for (auto x : a) cout << x << " ";
	cout << endl;

	quick_sort(b, 0, b.size() - 1);
	for (auto y : b) cout << y << " ";
	cout << endl;

	return 0;
}