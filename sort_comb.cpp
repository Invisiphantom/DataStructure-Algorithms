#include <iostream>
#include <string>
#include <vector>

using namespace std;

template <class T>
void comb_sort(vector<T>& _array) {
	auto gap = _array.size();
	while (gap >= 1) {
		gap = gap / 1.247331;
		for (size_t i = 0; i < _array.size() - gap; i++)
			if (_array[i] > _array[i + gap]) swap(_array[i], _array[i + gap]);
	}
}

int main() {
	vector<int> a = {5, 2, 4, 6, 1, 3};
	vector<string> b = {"a", "w", "h", "j", "m", "a", "c"};

	comb_sort(a);
	for (auto x : a) cout << x << " ";
	cout << endl;

	comb_sort(b);
	for (auto y : b) cout << y << " ";
	cout << endl;

	return 0;
}