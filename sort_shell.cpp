#include <iostream>
#include <string>
#include <vector>

using namespace std;

template <class T>
void shell_sort(vector<T>& _array) {
	auto gap = _array.size();
	while (gap > 1) {
		// gap = gap / 2;
        gap = gap / 3 + 1;
		for (auto j = gap; j < _array.size(); j++) {
			auto key = _array[j];
			auto i = j - gap;
			while (i < _array.size() && key < _array[i]) {
				_array[i + gap] = _array[i];
				i -= gap;
			}
			_array[i + gap] = key;
		}
	}
}

int main() {
	vector<int> a = {5, 2, 4, 6, 1, 3};
	vector<string> b = {"a", "w", "h", "j", "m", "a", "c"};

	shell_sort(a);
	for (auto x : a) cout << x << " ";
	cout << endl;

	shell_sort(b);
	for (auto y : b) cout << y << " ";
	cout << endl;

	return 0;
}