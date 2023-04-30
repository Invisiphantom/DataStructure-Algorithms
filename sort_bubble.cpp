#include <iostream>
#include <string>
#include <vector>

using namespace std;

template <class T>
void bubble_sort(vector<T> &_array) {
	for (size_t i = 0; i < _array.size() - 1; i++)
		for (size_t j = 0; j < _array.size() - 1 - i; j++)
			if (_array[j] > _array[j + 1]) swap(_array[j], _array[j + 1]);
}

int main() {
	vector<int> a = {5, 2, 4, 6, 1, 3};
	vector<string> b = {"a", "w", "h", "j", "m", "a", "c"};

	bubble_sort(a);
	for (auto x : a) cout << x << " ";
	cout << endl;

	bubble_sort(b);
	for (auto y : b) cout << y << " ";
	cout << endl;

	return 0;
}