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

struct Node {
  Node *l = 0, *r = 0;
  int val, y, c = 1;
  Node(int val) : val(val), y(rand()) {}
  void recalc();
};

int cnt(Node* n) { return n ? n->c : 0; }
void Node::recalc() { c = cnt(l) + cnt(r) + 1; }

pair<Node*, Node*> split(Node* n, int k) {
  if (!n) return {};
  if (n->val >= k) {  // "n->val >= k" for lower_bound(k)
    auto pa = split(n->l, k);
    n->l = pa.second;
    n->recalc();
    return {pa.first, n};
  } else {
    auto pa = split(n->r, k);  // and just "k"
    n->r = pa.first;
    n->recalc();
    return {n, pa.second};
  }
}

Node* merge(Node* l, Node* r) {
  if (!l) return r;
  if (!r) return l;
  if (l->y > r->y) {
    l->r = merge(l->r, r);
    l->recalc();
    return l;
  } else {
    r->l = merge(l, r->l);
    r->recalc();
    return r;
  }
}

Node* ins(Node* t, int val) {
  auto [l, r] = split(t, val);
  return merge(merge(l, new Node(val)), r);
}

Node* join(Node* l, Node* r) {
  if (!r) return l;
  l = ins(l, r->val);
  l = join(l, r->l);
  l = join(l, r->r);
  return l;
}

int countUnder(Node* n, int k) {
  if (!n) return 0;
  if (n->val >= k) return countUnder(n->l, k);
  return 1 + cnt(n->l) + countUnder(n->r, k);
}

Node* dfs(const vector<vi>& adj, vl& f, ll& addAll, int u = 0, int p = -1) {
  Node* subtree = new Node(u);

  for (auto v : adj[u]) {
    if (v == p) continue;
    Node* child = dfs(adj, f, addAll, v, u);

    ll curr = countUnder(child, u);
    addAll += curr, f[v] -= curr;
    if (cnt(subtree) < cnt(child)) swap(subtree, child);
    subtree = join(subtree, child);
  }

  ll curr = u - countUnder(subtree, u);
  f[u] += curr;
  return subtree;
}

void propagate(const vector<vi>& adj, vl& f, int u = 0, int p = -1) {
  for (auto v : adj[u]) {
    if (v == p) continue;
    f[v] += f[u];
    propagate(adj, f, v, u);
  }
}

int main() {
  cin.tie(0)->sync_with_stdio(0);

  int n;
  cin >> n;
  vector<vi> adj(n);
  rep(i, 0, n - 1) {
    int u, v;
    cin >> u >> v, u--, v--;
    adj[u].push_back(v), adj[v].push_back(u);
  }

  vl f(n);
  ll addAll = 0;
  dfs(adj, f, addAll);
  propagate(adj, f);

  rep(i, 0, n) cout << f[i] + addAll << " \n"[i + 1 == n];
}
