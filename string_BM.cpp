/**
 * @file string_BM.cpp
 * @author Invisiphatom (ethancao16770@gmail.com)
 * @brief function:build_good_table is based on pictures from
 * https://blog.csdn.net/qq_35423154/article/details/109137798?ops_request_misc=&request_id=&biz_id=102&utm_term=%E5%AD%97%E7%AC%A6%E4%B8%B2%E5%8C%B9%E9%85%8D%E7%AE%97%E6%B3%95%EF%BC%88%E4%BA%8C%EF%BC%89%EF%BC%9ABM&utm_medium=distribute.pc_search_result.none-task-blog-2~all~sobaiduweb~default-0-109137798.142^v83^pc_search_v2,201^v4^add_ask,239^v2^insert_chatgpt&spm=1018.2226.3001.4187
 * other parts are based on code from
 * https://blog.csdn.net/DBC_121/article/details/105569440
 * @version 0.1
 * @date 2023-04-12
 *
 * @copyright Copyright (c) 2023 Invisiphatom
 * All Rights Reserved.
 *
 */
#include <iostream>
#include <string>
#include <vector>

using namespace std;
const int TABLE_SIZE = 256;	 // set string's ANSIC range

int get_suffix_len(const string P, const int end) {
	int suffix_end = P.size() - 1;
	int midstr_end = end;
	int suffix_len = 0;
	while (midstr_end >= 0 && P[midstr_end] == P[suffix_end]) {
		suffix_len++;
		midstr_end--;
		suffix_end--;
	}
	return suffix_len;
}

bool judge_is_prefix(const string P, const int start) {
	int prefix_start = 0;
	int midstr_start = start;
	while (midstr_start < P.size()) {
		if (P[midstr_start] != P[prefix_start]) return false;
		midstr_start++;
		prefix_start++;
	}
	return true;
}

vector<int> build_bad_table(const string P) {
	vector<int> bad_table(TABLE_SIZE, P.size());
	// NOTE {P.size() - 1} -> The last element is excluded
	for (int pi = 0; pi < P.size() - 1; pi++)
		bad_table[P[pi]] = P.size() - (pi + 1);
	return bad_table;
}

vector<int> build_good_table(const string P) {
	vector<int> good_table(P.size(), 0);

	for (int pi = P.size() - 1, match_len = 0; pi != 0; pi--) {
		// reset match_len dynamically according to different pi
		if (judge_is_prefix(P, pi)) match_len = P.size() - (pi + 1);
		// (P.size() + (P.size() - (pi + 1))) -> excessive sliding
		// match_len -> relieve excessive sliding
		good_table[pi - 1] = (P.size() + (P.size() - (pi + 1))) - match_len;
	}

	// Sequential scanning, pairing middle string with corresponding suffix
	// NOTE {P.size() - 1} -> The last element is excluded
	for (int pi = 0; pi < P.size() - 1; pi++) {
		int suffix_len = get_suffix_len(P, pi);
		if (suffix_len != 0)
			good_table[P.size() - 1 - suffix_len] = P.size() - (pi - suffix_len + 1);
	}

	return good_table;
}

void BM_matcher(const string T, const string P) {
	if (P.size() > T.size()) return;

	auto bad_table = build_bad_table(P);
	auto good_table = build_good_table(P);

	auto ti = P.size() - 1;
	auto pi = P.size() - 1;
	while (ti < T.size()) {
		while (T[ti] == P[pi]) {
			if (pi == 0) {
				cout << "Match in position:  " << ti << endl;
				break;
			}
			ti--;
			pi--;
		}
		ti += max(bad_table[T[ti]], good_table[pi]);
		pi = P.size() - 1;
	}
}

int main() {
	string T = "HERE IS A SIMPLE EXAMPLE";
	string P = "EXAMPLE";
	BM_matcher(T, P);
	return 0;
}