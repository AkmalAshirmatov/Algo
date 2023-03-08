struct SegmentTree {
  ll t[4 * N], add[4 * N];

  void change(int v, ll val) {
    t[v] += val;
    add[v] += val;
  }

  void push(int v) {
    change(v * 2, add[v]);
    change(v * 2 + 1, add[v]);
    add[v] = 0;
  }

  ll get(int v, int tl, int tr, int l, int r) {
    if (l > r) {
      return INF;
    }
    if (tl == l && tr == r) {
      return t[v];
    }
    push(v);
    int tm = (tl + tr) >> 1;
    return min(get(v * 2, tl, tm, l, min(r, tm)),
               get(v * 2 + 1, tm + 1, tr, max(l, tm + 1), r));
  }

  void update(int v, int tl, int tr, int l, int r, ll val) {
    if (l > r) {
      return;
    }
    if (tl == l && tr == r) {
      change(v, val); return;
    }
    push(v);
    int tm = (tl + tr) >> 1;
    update(v * 2, tl, tm, l, min(r, tm), val);
    update(v * 2 + 1, tm + 1, tr, max(l, tm + 1), r, val);
    t[v] = min(t[v * 2], t[v * 2 + 1]);
  }
};

SegmentTree segTree;

//int v1 = v + 1, v2 = v + ((tm - tl + 1) << 1);
