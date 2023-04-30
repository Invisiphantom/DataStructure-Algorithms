#include <iostream>
#include <string>
#include <vector>

using namespace std;

template <class T>
void selection_sort(vector<T>& _array) {
	size_t begin = 0, end = _array.size() - 1;
	while (begin < end) {
		int min_index = begin, max_index = begin;
		for (size_t i = begin; i <= end; i++) {
			if (_array[i] < _array[min_index]) min_index = i;
			if (_array[i] > _array[max_index]) max_index = i;
		}
		swap(_array[begin], _array[min_index]);
		swap(_array[end], _array[max_index]);
		begin++;
		end--;
	}
}

int main() {
	vector<int> a = {5, 2, 4, 6, 1, 3};
	vector<string> b = {"a", "w", "h", "j", "m", "a", "c"};

	selection_sort(a);
	for (auto x : a) cout << x << " ";
	cout << endl;

	selection_sort(b);
	for (auto y : b) cout << y << " ";
	cout << endl;

	return 0;
}