#include <bits/stdc++.h>

using namespace std;

int main() {
  cin.tie(0)->sync_with_stdio(false);

  int t;
  cin >> t;
  while (t--) {
    int n, q;
    cin >> n >> q;

    vector<int> a(n), nonZero;
    for (int i = 0; i < n; i++) {
      cin >> a[i];

      // Store indices where a is non-zero
      if (a[i] != 0) nonZero.push_back(i);
    }

    // Compute the prefix XOR of a
    vector<int> pfxXOR(n + 1);
    for (int i = 0; i < n; i++) pfxXOR[i + 1] = pfxXOR[i] ^ a[i];

    // Each query runs in O(log n + log X), we run two Binary Searches, and i / j move O(log X) times
    while (q--) {
      int L, R;
      cin >> L >> R, L--;

      // Find first and last index non-zero indices in [L, R]
      int i = (int)(lower_bound(nonZero.begin(), nonZero.end(), L) - nonZero.begin());
      int j = (int)(lower_bound(nonZero.begin(), nonZero.end(), R) - nonZero.begin()) - 1;

      // Compute the XOR of [L, R]
      int currXOR = 0;
      const int segmentXOR = pfxXOR[L] ^ pfxXOR[R];

      const auto canExpand = [&](int x) {
        // We can expand the border with element x if we have no repeat bits in currXOR,
        // and currXOR remains a submask of segmentXOR
        return ((currXOR & x) == 0) && ((segmentXOR & x) == x);
      };

      // Expand the border from the left as much as possible
      const auto expandLeft = [&]() {
        while (i < (int)(nonZero.size()) && nonZero[i] < R && canExpand(a[nonZero[i]])) {
          currXOR ^= a[nonZero[i]];
          i++;
        }
      };

      // Similarly, expand the border from the right as much as possible
      const auto expandRight = [&]() {
        while (j >= 0 && nonZero[j] >= L && canExpand(a[nonZero[j]])) {
          currXOR ^= a[nonZero[j]];
          j--;
        }
      };

      expandLeft(), expandRight();

      // We can remove every non-zero element, we take the some subsegment of length 1
      if (i == (int)(nonZero.size()) || nonZero[i] >= R) {
        cout << L + 1 << " " << L + 1 << '\n';
        continue;
      }

      // Shift the window, by removing i from the left, and expanding to the right in each step
      pair<int, int> best = {nonZero[i], nonZero[j]};
      while (i > 0 && nonZero[i - 1] >= L) {
        i--;
        currXOR ^= a[nonZero[i]];
        expandRight();

        if (best.second - best.first > nonZero[j] - nonZero[i]) best = {nonZero[i], nonZero[j]};
      }

      cout << best.first + 1 << " " << best.second + 1 << '\n';
    }
  }
}