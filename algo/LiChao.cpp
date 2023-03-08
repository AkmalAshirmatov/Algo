const int N = 1e3 + 10;
const int INF = 1e9;

struct LN {
  int k, b;

  int f(int x) {
    return k * x + b;
  }
};

struct LiChao {
  LN t[4 * N];

  void addLine(int v, int tl, int tr, LN nw) {
    if (t[v].f(tl) <= nw.f(tl) && t[v].f(tr) <= nw.f(tr)) {
      return;
    }
    if (nw.f(tl) <= t[v].f(tl) && nw.f(tr) <= t[v].f(tr)) {
      t[v] = nw; return;
    }
    if (tl + 1 == tr)
      return;
    int tm = (tl + tr) >> 1;
    bool lef = nw.f(tl) < t[v].f(tl);
    bool mid = nw.f(tm) < t[v].f(tm);
    if (mid)
      swap(t[v], nw);
    if (lef != mid)
      addLine(v * 2, tl, tm, nw);
    else
      addLine(v * 2 + 1, tm, tr, nw);
  }

  int get(int v, int tl, int tr, int x) {
    if (tl + 1 == tr)
      return t[v].f(x);
    int tm = (tl + tr) >> 1;
    if (x < tm)
      return min(t[v].f(x), get(2 * v, tl, tm, x));
    else
      return min(t[v].f(x), get(2 * v + 1, tm, tr, x));
  }
};




#include <bits/stdc++.h>

using namespace std;

#define all(x) (x).begin(), (x).end()

typedef long long ll;

double ptIntersect(pair <ll, ll>  a, pair <ll, ll> b){
  return (b.second - a.second) * 1.0 / (double)(a.first - b.first);
}

vector<pair<ll, ll> > lowerConvexHull;

void addLine(pair<ll, ll> ln) {
  while (lowerConvexHull.size() >= 2 && ptIntersect(lowerConvexHull[lowerConvexHull.size() - 2], lowerConvexHull.back()) >= ptIntersect(lowerConvexHull.back(), ln)) lowerConvexHull.pop_back();
  lowerConvexHull.push_back(ln);
}

ll findMin(ll x) {
  int l = 1, r = lowerConvexHull.size() - 1, need = 0;
  while (l <= r) {
    int m = (l + r) >> 1;
    if (ptIntersect(lowerConvexHull[m - 1], lowerConvexHull[m]) <= x)
      l = m + 1, need = m;
    else
      r = m - 1;
  }
  return lowerConvexHull[need].first * x + lowerConvexHull[need].second;
}

const int N = 1e5;
ll a[N], b[N], dp[N];

void solve() {
  int n; cin >> n;
  for (int i = 0; i < n; i++) {
    cin >> a[i];
  }
  for (int i = 0; i < n; i++) {
    cin >> b[i];
  }
  dp[0] = 0;
  addLine({b[0], dp[0]});
  for (int i = 1; i < n; i++) {
    dp[i] = findMin(a[i]);
    addLine({b[i], dp[i]});
  }
  cout << dp[n - 1];
}
