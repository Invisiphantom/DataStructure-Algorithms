#include <benchmark/benchmark.h>

#include <algorithm>
#include <deque>
#include <iostream>
#include <random>
#include <vector>

using namespace std;

static const int _num = 30000;
static const int _iter = 1;

vector<int> test_array = vector<int>(_num);

void init() {
	for (int i = 0; i < _num; ++i) {
		test_array.emplace_back(i);
	}
}

template <class T>
void selection_sort(vector<T>& _array);
static void BM_selection_sort(benchmark::State& state) {
	for (auto _ : state) {
		random_shuffle(test_array.begin(), test_array.end());
		selection_sort(test_array);
	}
}
BENCHMARK(BM_selection_sort)->Iterations(_iter);

template <class T>
void bubble_sort(vector<T>& _array);
static void BM_bubble_sort(benchmark::State& state) {
	for (auto _ : state) {
		random_shuffle(test_array.begin(), test_array.end());
		bubble_sort(test_array);
	}
}
BENCHMARK(BM_bubble_sort)->Iterations(_iter);

template <class T>
void comb_sort(vector<T>& _array);
static void BM_comb_sort(benchmark::State& state) {
	for (auto _ : state) {
		random_shuffle(test_array.begin(), test_array.end());
		comb_sort(test_array);
	}
}
BENCHMARK(BM_comb_sort)->Iterations(_iter);

template <class T>
void insertion_sort(vector<T>& _array);
static void BM_insertion_sort(benchmark::State& state) {
	for (auto _ : state) {
		random_shuffle(test_array.begin(), test_array.end());
		insertion_sort(test_array);
	}
}
BENCHMARK(BM_insertion_sort)->Iterations(_iter);

template <class T>
void shell_sort(vector<T>& _array);
static void BM_shell_sort(benchmark::State& state) {
	for (auto _ : state) {
		random_shuffle(test_array.begin(), test_array.end());
		shell_sort(test_array);
	}
}
BENCHMARK(BM_shell_sort)->Iterations(_iter);

template <class T>
void heap_sort(vector<T>& _array);
static void BM_heap_sort(benchmark::State& state) {
	for (auto _ : state) {
		random_shuffle(test_array.begin(), test_array.end());
		heap_sort(test_array);
	}
}
BENCHMARK(BM_heap_sort)->Iterations(_iter);

template <class T>
void Merge_sort(vector<T>& _array);
static void BM_Merge_sort(benchmark::State& state) {
	for (auto _ : state) {
		random_shuffle(test_array.begin(), test_array.end());
		Merge_sort(test_array);
	}
}
BENCHMARK(BM_Merge_sort)->Iterations(_iter);

template <class T>
void Quick_sort(vector<T>& _array);
static void BM_Quick_sort(benchmark::State& state) {
	for (auto _ : state) {
		random_shuffle(test_array.begin(), test_array.end());
		Quick_sort(test_array);
	}
}
BENCHMARK(BM_Quick_sort)->Iterations(_iter);

template <class T>
void STL_sort(vector<T>& _array);
static void BM_STL_sort(benchmark::State& state) {
	for (auto _ : state) {
		random_shuffle(test_array.begin(), test_array.end());
		STL_sort(test_array);
	}
}
BENCHMARK(BM_STL_sort)->Iterations(_iter);

int main(int argc, char** argv) {
	init();
	::benchmark::Initialize(&argc, argv);
	::benchmark::RunSpecifiedBenchmarks();
}

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

template <class T>
void bubble_sort(vector<T>& _array) {
	for (size_t i = 0; i < _array.size() - 1; i++)
		for (size_t j = 0; j < _array.size() - 1 - i; j++)
			if (_array[j] > _array[j + 1]) swap(_array[j], _array[j + 1]);
}

template <class T>
void comb_sort(vector<T>& _array) {
	auto gap = _array.size();
	while (gap >= 1) {
		gap = gap / 1.247331;
		for (size_t i = 0; i < _array.size() - gap; i++)
			if (_array[i] > _array[i + gap]) swap(_array[i], _array[i + gap]);
	}
}

template <class T>
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

template <class T>
void heap_sort(vector<T>& _array) {
	make_heap(_array.begin(), _array.end());
	sort_heap(_array.begin(), _array.end());
}

template <class T>
void merge(vector<T>& _array, const size_t left, const size_t right,
					 const size_t mid) {
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
void merge_sort(vector<T>& _array, const size_t left, const size_t right) {
	if (left != right) {
		size_t mid = size_t((left + right) / 2);
		merge_sort(_array, left, mid);
		merge_sort(_array, mid + 1, right);
		merge(_array, left, right, mid);
		// inplace_merge(_array.begin() + left, _array.begin() + mid + 1,
		//                      _array.begin() + right + 1, greater<T>());
	}
}

template <class T>
void Merge_sort(vector<T>& _array) {
	merge_sort(_array, 0, _array.size() - 1);
}

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

template <class T>
void Quick_sort(vector<T>& _array) {
	quick_sort(_array, 0, _array.size() - 1);
}

template <class T>
void STL_sort(vector<T>& _array) {
	sort(_array.begin(), _array.end());
}