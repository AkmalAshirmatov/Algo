struct VRT {
  int l, r, hash, ans;
};

vector<VRT> nodes;

void recalc(int v, int tl, int tm, int tr) {
  int hs = 0, ans = 0;
  if (nodes[v].l != -1) {
    add(hs, nodes[nodes[v].l].hash);
    add(ans, nodes[nodes[v].l].ans);
  }
  if (nodes[v].r != -1) {
    add(hs, mul(nodes[nodes[v].r].hash, pw[tm - tl + 1]));
    add(ans, nodes[nodes[v].r].ans);
  }
  nodes[v].hash = hs, nodes[v].ans = ans;
}

int build(int tl, int tr, int value) {
  if (tl == tr) {
    nodes.push_back({-1, -1, 0, 0});
    if (value == tl) {
      nodes.back().hash++;
      nodes.back().ans = wr[tl];
    }
    return nodes.size() - 1;
  }
  int tm = (tl + tr) >> 1;
  int l = build(tl, tm, value), r = build(tm + 1, tr, value);
  int v = nodes.size();
  nodes.push_back({l, r, 0});
  recalc(v, tl, tm, tr);
  return v;
}

int update(int v, int tl, int tr, int pos, int flag = 0) {
  if (tl == tr) {
    int cnt = nodes[v].hash + (flag == 0 ? 1 : -1), ans = 0;
    if (flag == 0)
      ans = sum(nodes[v].ans, wr[tl]);
    else
      ans = sum(nodes[v].ans, -wr[tl]);
    nodes.push_back({-1, -1, cnt, ans});
    return nodes.size() - 1;
  }
  int tm = (tl + tr) >> 1;
  if (pos <= tm) {
    int lft = update(nodes[v].l, tl, tm, pos, flag);
    nodes.push_back(nodes[v]); nodes.back().l = lft; v = nodes.size() - 1;
  }
  else {
    int rgt = update(nodes[v].r, tm + 1, tr, pos, flag);
    nodes.push_back(nodes[v]); nodes.back().r = rgt; v = nodes.size() - 1;
  }
  recalc(v, tl, tm, tr);
  return v;
}

bool cmp(int v1, int v2) {
  int tl = 0, tr = n * n - 1;
  while (tl != tr) {
    int tm = (tl + tr) >> 1;
    if (nodes[nodes[v1].l].hash != nodes[nodes[v2].l].hash) {
      v1 = nodes[v1].l; v2 = nodes[v2].l;
      tr = tm;
    }
    else {
      v1 = nodes[v1].r; v2 = nodes[v2].r;
      tl = tm + 1;
    }
  }
  return nodes[v1].hash > nodes[v2].hash;
}

int getmax(int v1, int v2) {
  if (nodes[v1].hash == nodes[v2].hash) {
    return v1;
  }
  return (cmp(v1, v2) ? v1 : v2);
}
