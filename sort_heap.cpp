#include <algorithm>
#include <iostream>
#include <string>
#include <vector>

using namespace std;

template <class T>
void heap_sort(vector<T>& _array) {
    make_heap(_array.begin(), _array.end());
	sort_heap(_array.begin(), _array.end());
}

int main() {
	vector<int> a = {5, 2, 4, 6, 1, 3};
	vector<string> b = {"a", "w", "h", "j", "m", "a", "c"};

	heap_sort(a);
	for (auto x : a) cout << x << " ";
	cout << endl;

	heap_sort(b);
	for (auto y : b) cout << y << " ";
	cout << endl;

	return 0;
}