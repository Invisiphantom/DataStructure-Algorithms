/**
 * @file string_KMP.cpp
 * @author Invisiphatom (ethancao16770@gmail.com)
 * @brief following CLRS P590
 * @version 0.1
 * @date 2023-04-11
 * 
 * @copyright Copyright (c) 2023 Invisiphatom
 * All Rights Reserved.
 * 
 */
#include <iostream>
#include <string>
#include <vector>

using namespace std;

auto get_prefix(const string P) {
	vector<int> pre{0};
	for (size_t str_i = 1, pre_i = 0; str_i < P.size(); str_i++) {
		while (pre_i > 0 && P[pre_i] != P[str_i])
			pre_i = pre[pre_i - 1];	 // jump back to smaller prefix substring
		if (P[pre_i] == P[str_i]) pre_i++;
		pre.emplace_back(pre_i);
	}
	return pre;
}

auto KMP_matcher(const string T, const string P) {
	auto pre = get_prefix(P);
	for (size_t i = 0, j = 0; i < T.size(); i++) {
		while (j != 0 && T[i] != P[j]) j = pre[j - 1];
		if (T[i] == P[j]) j++;
		if (j == P.size()) cout << "Match in position:  " << i - j + 1 << endl;
	}
}

int main() {
	string T = "abababbabffoe";
	string P = "oe";
	KMP_matcher(T, P);
	return 0;
}

// auto KMP_matcher(string T, string P) {
// 	auto pre = get_prefix(P);
// 	size_t i = 0, j = 0;
// 	while (i < T.size()) {
// 		if (T[i] == P[j]) {	 // if equal, slide together
// 			i++;
// 			j++;
// 			if (j == P.size()) cout << "Match in position:  " << i - j << endl;
// 		} else if (j != 0)	 // if not equal, jump to smaller prefix substring
// 			j = pre[j - 1];
// 		else	// even the first elements don't match, skip to T[i+1]
// 			i++;
// 	}
// }