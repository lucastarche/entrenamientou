#include "equal.h"

#include <vector>
#define rep(i, a, b) for (int i = (int)(a); i < (int)(b); ++i)
#define per(i, a, b) for (int i = (int)(b) - 1; i >= (int)(a); --i)
#define all(x) begin(x), end(x)

using namespace std;
using vi = vector<int>;

const int BITS = 20;

void make_all_equal(int N, int Q_add, int Q_compare) {
  int k = 0;
  while ((1 << k) != N) k++;

  per(b, 0, k - 1) {
    vi v;
    rep(i, 0, N / 2) if (i & (1 << b)) v.push_back(2 * i), v.push_back(2 * i + 1);
    add(v, 1 << (BITS + b));
  }

  int X = 1 << BITS;
  for (int step = 1; step < N; step *= 2) {
    vi toAdd;
    for (int i = 0; i < N; i += 2 * step) {
      rep(j, i, i + step) toAdd.push_back(j);
    }

    per(b, 0, BITS) add(toAdd, 1 << b);

    toAdd.clear();
    for (int i = 0; i < N; i += 2 * step) {
      if (not compare(i, i + step)) {
        rep(j, i, i + step) toAdd.push_back(j);
      }
    }
    add(toAdd, 1);

    toAdd.clear();
    for (int i = 0; i < N; i += 4 * step) {
      rep(j, i, i + 2 * step) toAdd.push_back(j);
    }
    add(toAdd, X);
    X *= 2;
  }
}
