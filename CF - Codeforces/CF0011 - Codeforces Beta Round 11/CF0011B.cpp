#include <bits/stdc++.h>

using namespace std;

int main() {
  cin.tie(0)->sync_with_stdio(false);

  int x;
  cin >> x;
  x = abs(x);

  int k = 0, sum = 0;
  while (sum < x || sum % 2 != x % 2) {
    k++;
    sum += k;
  }
  cout << k << '\n';
}