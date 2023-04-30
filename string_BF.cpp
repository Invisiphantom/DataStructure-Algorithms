/**
 * @file string_naive.cpp
 * @author Invisiphatom (ethancao16770@gmail.com)
 * @brief following CLRS P579
 * @version 0.1
 * @date 2023-04-11
 *
 * @copyright Copyright (c) 2023 Invisiphatom
 * All Rights Reserved.
 *
 */
#include <iostream>
#include <string>

using namespace std;

void naive_string_matcher(const string T, const string P) {
	int n = T.size(), m = P.size();
	for (int s = 0; s <= (n - m); s++) {
		if (T.compare(s, m, P) == 0) cout << "Match in position:  " << s << endl;
	}
}

int main() {
	string a = "acaabc";
	string b = "a";
	naive_string_matcher(a, b);
	return 0;
}