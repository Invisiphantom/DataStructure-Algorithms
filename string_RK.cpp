/**
 * @file string_RK.cpp
 * @author Invisiphatom (ethancao16770@gmail.com)
 * @brief following CLRS P582
 * @version 0.1
 * @date 2023-04-11
 *
 * @copyright Copyright (c) 2023 Invisiphatom
 * All Rights Reserved.
 *
 */
#include <cmath>
#include <iostream>
#include <string>
#include <vector>

using namespace std;

void Rabin_Karp_matcher(const vector<int>& Text, const vector<int>& Pattern,
												const int _base, const int _mod) {
	int len_T = Text.size(), len_M = Pattern.size();
	int high_digit = (int)pow(_base, len_M - 1) % _mod;
	int num_P = 0, num_T = 0;
	for (int i = 0; i < len_M; i++) {
		num_P = (_base * num_P + Pattern[i]) % _mod;
		num_T = (_base * num_T + Text[i]) % _mod;
	}
	for (int s = 0; s <= (len_T - len_M); s++) {
		if (num_P == num_T)
			if (equal(Text.begin() + s, Text.begin() + s + len_M, Pattern.begin()))
				cout << "Match in position:  " << s << endl;
		if (s < (len_T - len_M))
			num_T = (_base * (num_T - Text[s] * high_digit) + Text[s + len_M]) % _mod;
	}
}

int main() {
	vector<int> a = {0, 1, 2, 2};
	vector<int> b = {2};
	Rabin_Karp_matcher(a, b, 10, 13);
	return 0;
}