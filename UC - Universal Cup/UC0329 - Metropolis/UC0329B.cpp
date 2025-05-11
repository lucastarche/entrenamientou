#include <bits/stdc++.h>
#define rep(i, a, b) for (int i = (int)(a); i < (int)(b); ++i)
#define sz(x) (int)(x.size())
#define all(x) x.begin(), x.end()
#define DBG(x) cerr << #x << " = " << x << endl

using namespace std;
using ll = long long;
using pii = pair<int, int>;
using vi = vector<int>;
using vii = vector<pii>;
using vb = vector<bool>;
using vl = vector<ll>;

vector<vector<int>> g;
vector<bool> visited;
vector<int> order, orderInv;

vector<pair<int, int>> added;
int n, m;

int dfs(int curr, int i, int root) {
  // DBG(orderInv[curr]);

  visited[curr] = true;
  int nextI = i + 1;

  for (auto &e : g[curr]) {
    // DBG(orderInv[e]);
    // DBG(orderInv[nextI]);
    if (e < nextI) continue;
    while (e >= nextI) {
      if (e == nextI) {
        nextI = dfs(e, nextI, root);
      } else {
        added.push_back({curr, nextI});
        assert(!visited[e]);
        nextI = dfs(nextI, nextI, root);
      }
    }
  }

  if (nextI != n && root == curr) {
    dfs(nextI, nextI, nextI);
  }

  return nextI;
}

int main() {
  cin.tie(0)->sync_with_stdio(false);

  cin >> n >> m;

  g.resize(n);
  vector<pair<int, int>> nums;

  rep(i, 0, m) {
    int from, to;
    cin >> from >> to;
    nums.push_back({from, to});
  }

  order.resize(n + 1);
  orderInv.resize(n + 1);

  rep(i, 0, n) {
    int temp;
    cin >> temp;
    order[temp] = i;
    orderInv[i] = temp;
  }

  for (auto &[from, to] : nums) {
    from = order[from], to = order[to];
    g[from].push_back(to);
    g[to].push_back(from);
  }

  for (auto &edges : g) sort(all(edges));

  visited.resize(n + 1);
  dfs(0, 0, 0);

  cout << sz(added) << "\n";
  for (auto &[from, to] : added) {
    cout << orderInv[from] << " " << orderInv[to] << "\n";
  }
}