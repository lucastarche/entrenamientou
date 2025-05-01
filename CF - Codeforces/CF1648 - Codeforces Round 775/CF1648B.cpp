#include <bits/stdc++.h>

using namespace std;

int main() {
  int t;
  cin >> t;

  while (t--) {
    int n, c;
    cin >> n >> c;

    vector<int> a(n);
    vector<bool> present(c + 1);
    for (int i = 0; i < n; i++) cin >> a[i], present[a[i]] = true;

    sort(a.begin(), a.end());
    // Filter repeat elements from a, otherwise we would run repeat checks and break the O(n log c) bound
    a.erase(unique(a.begin(), a.end()), a.end());

    bool valid = true;

    // a is strictly increasing, so we iterate over O(n log c) pairs (y, k)
    for (auto y : a) {
      for (int k = 1; k * y <= c; k++) {
        if (present[k]) continue;

        // This binary search takes O(log n) time per pair (y, k)
        auto iter = lower_bound(a.begin(), a.end(), k * y);

        if (iter != a.end() && *iter < (k + 1) * y) {
          // k is missing from the array, but we found an x such that floor(x / y) = k
          valid = false;
          break;
        }
      }

      if (not valid) break;
    }

    cout << (valid ? "Yes" : "No") << '\n';
  }
}