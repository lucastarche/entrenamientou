#include <bits/stdc++.h>
#define rep(i, a, b) for (int i = a; i < (b); ++i)
#define per(i, a, b) for (int i = (int)(b) - 1; i >= (a); --i)
#define all(x) begin(x), end(x)
#define sz(x) (int)(x).size()

using namespace std;
using ll = long long;
using pii = pair<int, int>;
using vi = vector<int>;
using vii = vector<pii>;
using vb = vector<bool>;
using vl = vector<ll>;

const int INF = 1e9;
const int dx[8] = {1, 1, -1, -1, 2, 2, -2, -2};
const int dy[8] = {2, -2, 2, -2, 1, -1, 1, -1};

int main() {
  cin.tie(0)->sync_with_stdio(0);

  int n;
  cin >> n;

  queue<pii> q;
  vector<vi> dist(n, vi(n, INF));
  q.emplace(0, 0);
  dist[0][0] = 0;

  vector<vb> seen(n, vb(n));
  while (not q.empty()) {
    auto [x, y] = q.front();
    q.pop();

    if (seen[x][y]) continue;
    seen[x][y] = true;

    rep(k, 0, 8) {
      int nx = x + dx[k], ny = y + dy[k];
      if (nx < 0 || ny < 0 || nx >= n || ny >= n) continue;
      if (dist[nx][ny] > dist[x][y] + 1) {
        dist[nx][ny] = dist[x][y] + 1;
        q.emplace(nx, ny);
      }
    }
  }
  rep(i, 0, n) rep(j, 0, n) cout << dist[i][j] << " \n"[j + 1 == n];
}
