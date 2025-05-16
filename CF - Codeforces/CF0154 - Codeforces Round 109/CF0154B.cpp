#include <bits/stdc++.h>

using namespace std;

// Precompute the small divisor of x for every x <= n
vector<int> sieve(int n) {
  vector<int> smallestPrime(n + 1, -1);

  for (int p = 2; p <= n; p++) {
    if (smallestPrime[p] != -1) continue;
    smallestPrime[p] = p;
    for (int x = 2 * p; x <= n; x += p) {
      if (smallestPrime[x] == -1) smallestPrime[x] = p;
    }
  }

  return smallestPrime;
}

int main() {
  cin.tie(0)->sync_with_stdio(false);

  int n, q;
  cin >> n >> q;
  const auto smallestPrime = sieve(n);

  vector<bool> isOn(n + 1, false);
  vector<int> reactorByPrime(n + 1, -1);

  // Check if there is a reactor which conflicts with x
  // If so, return this number
  const auto check = [&](int x) -> int {
    while (x > 1) {
      int p = smallestPrime[x];
      if (reactorByPrime[p] != -1) return reactorByPrime[p];
      x /= p;
    }
    return -1;
  };

  // Turn on reactor x, and mark every prime divisor of x as having a reactor turned on
  const auto turnOn = [&](int x) {
    isOn[x] = true;
    int reactor = x;
    while (x > 1) {
      int p = smallestPrime[x];
      reactorByPrime[p] = reactor;
      x /= p;
    }
  };

  // Turn off reactor x, and reset every prime divisor of x
  const auto turnOff = [&](int x) {
    isOn[x] = false;
    while (x > 1) {
      int p = smallestPrime[x];
      reactorByPrime[p] = -1;
      x /= p;
    }
  };

  while (q--) {
    char type;
    int x;
    cin >> type >> x;

    if (type == '+') {
      if (isOn[x]) {
        cout << "Already on" << '\n';
        continue;
      }

      int reactor = check(x);
      if (reactor == -1) {
        cout << "Success" << '\n';
        turnOn(x);
      } else {
        cout << "Conflict with " << reactor << '\n';
      }
    } else {
      if (not isOn[x]) {
        cout << "Already off" << '\n';
        continue;
      }

      cout << "Success" << '\n';
      turnOff(x);
    }
  }
}