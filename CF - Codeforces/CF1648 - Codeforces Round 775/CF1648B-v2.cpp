/*
Similar al anterior, pero me puedo ahorrar la binaria si precomputo mínimo elemento más grande que $x$ para todo $x$, me fijo a la derecha de $ky$.
Raro que resulta ser casi tan rápido como el código anterior, difieren en $\approx 100\text{ms}$, cuando el código tarda $\approx 1200\text{ms}$. 
*/
#include <bits/stdc++.h>

using namespace std;
const int INF = 1e9;

int main() {
  int t;
  cin >> t;

  while (t--) {
    int n, c;
    cin >> n >> c;

    vector<int> sfxMin(c + 1, INF);
    for (int i = 0; i < n; i++) {
      int x;
      cin >> x;
      sfxMin[x] = x;
    }

    for (int i = c - 1; i >= 0; i--) sfxMin[i] = min(sfxMin[i], sfxMin[i + 1]);

    bool valid = true;
    for (int y = 0; y <= c; y++) {
      if (sfxMin[y] != y) continue;

      for (int k = 1; k * y <= c; k++) {
        valid &= (sfxMin[k] == k) || (sfxMin[k * y] >= (k + 1) * y);

        if (not valid) break;
      }
      if (not valid) break;
    }

    cout << (valid ? "Yes" : "No") << '\n';
  }
}
