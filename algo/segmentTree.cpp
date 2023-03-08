struct SegmentTree {
  int t[4 * N];

  ll get(int v, int tl, int tr, int l, int r) {
    if (l > r) {
      return INF;
    }
    if (tl == l && tr == r) {
      return t[v];
    }
    int tm = (tl + tr) >> 1;
    return min(get(v * 2, tl, tm, l, min(r, tm)),
      get(v * 2 + 1, tm + 1, tr, max(l, tm + 1), r));
  }

  void update(int v, int tl, int tr, int pos, ll val) {
    if (tl == tr) {
      t[v] += val;
      return;
    }
    int tm = (tl + tr) >> 1;
    if (pos <= tm)
      update(v * 2, tl, tm, pos, val);
    else
      update(v * 2 + 1, tm + 1, tr, pos, val);
    t[v] = min(t[v * 2], t[v * 2 + 1]);
  }
};

//int v1 = v + 1, v2 = v + ((tm - tl + 1) << 1);

int get(int v, int l, int r, int L, int R, int x) { // найти самое левое число, не делящееся на х на интервале [L, R]
  if (L >= R)
    return 0;
  if (l == L && r == R && t[v] % x == 0)
    return r - l;
  if (l == L && r == R && l == r - 1)
    return 0;
  int m = (l + r) / 2;
  int cnt = get(v * 2, l, m, L, min(m, R), x);
  if (cnt < max(0, min(m, R) - L))
    return cnt;
  return cnt + get(v * 2 + 1, m, r, max(m, L), R, x);
}
