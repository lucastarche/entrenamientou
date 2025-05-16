#include <bits/stdc++.h>

using namespace std;
using ll = long long;

const int SIGMA = 26;
using Freq = array<int, SIGMA>;

const int INF = 1e9;
const ll MOD = 998244353;

int main() {
  cin.tie(0)->sync_with_stdio(false);

  int n;
  cin >> n;

  vector<Freq> freq(n);
  for (int i = 0; i < n; i++) {
    string s;
    cin >> s;

    fill(freq[i].begin(), freq[i].end(), 0);
    for (auto c : s) freq[i][c - 'a']++;
  }

  // Compute the number of common subsequences of every string in the mask,
  // negated if the mask has an even number of bits
  vector<ll> f(1 << n);

  for (int mask = 1; mask < (1 << n); mask++) {  // Skip the empty subset
    Freq minFreq;
    fill(minFreq.begin(), minFreq.end(), INF);

    // Compute the minimum frequency of each character over strings in the mask
    for (int i = 0; i < n; i++) {
      if ((mask >> i) & 1) {
        for (int c = 0; c < SIGMA; c++) minFreq[c] = min(minFreq[c], freq[i][c]);
      }
    }

    f[mask] = 1;
    for (int c = 0; c < SIGMA; c++) f[mask] = (f[mask] * (minFreq[c] + 1)) % MOD;
    if (__builtin_popcount(mask) % 2 == 0) f[mask] = (MOD - f[mask]) % MOD;
  }

  // Sum-over-Subsets DP, compute the cumulative value
  for (int b = 0; b < n; b++) {
    for (int mask = 0; mask < (1 << n); mask++) {
      if ((mask >> b) & 1) continue;
      f[mask | (1 << b)] = (f[mask | (1 << b)] + f[mask]) % MOD;
    }
  }

  // Compute the hash value for the answer
  ll ans = 0;
  for (int mask = 0; mask < (1 << n); mask++) {
    ll indexSum = 0, k = 0;
    for (int i = 0; i < n; i++) {
      if ((mask >> i) & 1) indexSum += (i + 1), k++;
    }
    ans ^= f[mask] * indexSum * k;
  }
  cout << ans << '\n';
}