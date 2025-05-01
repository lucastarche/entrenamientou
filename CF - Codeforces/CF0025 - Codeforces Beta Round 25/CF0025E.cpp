#include <bits/stdc++.h>

using namespace std;

const int SIGMA = 26;

vector<int> pi(const string &s) {
  vector<int> p(s.size());
  for (int i = 1; i < (int)(s.size()); i++) {
    int g = p[i - 1];
    while (g && s[i] != s[g]) g = p[g - 1];
    p[i] = g + (s[i] == s[g]);
  }

  // pi[0] = 0
  p.insert(p.begin(), 0);
  return p;
}

vector<array<int, SIGMA>> automaton(const string &s) {
  const auto p = pi(s);
  vector<array<int, SIGMA>> f(s.size() + 1);
  for (int i = 0; i <= (int)(s.size()); i++) fill(f[i].begin(), f[i].end(), 0);

  for (int i = 0; i < (int)(s.size()); i++) {
    for (int c = 0; c < SIGMA; c++) {
      if (s[i] - 'a' == c) {
        // We matched an additional character, extend the prefix by one
        f[i][c] = i + 1;
      } else {
        // We shrink the prefix the smallest amount possible, and then add c
        f[i][c] = f[p[i]][c];
      }
    }
  }

  // If x = |s|, f(x, c) = f(pi(x), c)
  for (int c = 0; c < SIGMA; c++) f.back()[c] = f[p.back()][c];
  return f;
}

int solve(const string &s1, const string &s2, const string &s3) {
  const int n1 = (int)s1.size(), n2 = (int)s2.size(), n3 = (int)s3.size();

  int prefixS2 = 0, prefixS3 = 0;
  bool matchedS2 = false, matchedS3 = false;
  const auto f_s2 = automaton(s2), f_s3 = automaton(s3);

  int ans = 0;
  // Add a character to the answer
  const auto add = [&](char c) {
    ans++;
    prefixS2 = f_s2[prefixS2][c - 'a'];
    prefixS3 = f_s3[prefixS3][c - 'a'];
    matchedS2 |= (prefixS2 == n2);
    matchedS3 |= (prefixS3 == n3);
  };

  // Add s1
  for (int i = 0; i < n1; i++) add(s1[i]);
  // Add the remaining characters of s2, if we have yet to match it
  if (not matchedS2) for (int i = prefixS2; i < n2; i++) add(s2[i]);
  // Do the same for s3
  if (not matchedS3) for (int i = prefixS3; i < n3; i++) add(s3[i]);

  return ans;
}

int main() {
  string s1, s2, s3;
  cin >> s1 >> s2 >> s3;

  // The answer is the minimum number of characters across every permutation of [s1, s2, s3]
  int ans = min({
      solve(s1, s2, s3),
      solve(s1, s3, s2),
      solve(s2, s1, s3),
      solve(s2, s3, s1),
      solve(s3, s1, s2),
      solve(s3, s2, s1),
  });

  cout << ans << '\n';
}