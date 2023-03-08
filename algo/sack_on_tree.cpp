vector<int> edges[N];
int tin[N], tout[N], timer = 0;
int euler[N];
int sz[N], h[N], cnt[N], ans[N];
void dfs_sz(int v, int p = -1) {
  tin[v] = timer;
  euler[timer] = v;
  timer++;
  sz[v] = 1;
  for (int u : edges[v]) {
    if (u == p) continue;
    h[u] = h[v] + 1;
    dfs_sz(u, v);
    sz[v] += sz[u];
  }
  tout[v] = timer;
}
int curmaxh = 0, curmaxval = 0;
void upd(int nh) {
  if (curmaxval < cnt[nh] || curmaxval == cnt[nh] && curmaxh > nh) {
    curmaxval = cnt[nh], curmaxh = nh;
  }
}
void dfs(int v, int p = -1, int flag = 1) {
  int big_child = -1;
  for (int u : edges[v]) {
    if (u == p) continue;
    if (big_child == -1 || sz[big_child] < sz[u]) {
      big_child = u;
    }
  }
  for (int u : edges[v]) {
    if (u == p || u == big_child) continue;
    dfs(u, v, 1);
  }
  if (big_child != -1) {
    dfs(big_child, v, 0);
  }
  cnt[h[v]]++;
  upd(h[v]);
  for (int u : edges[v]) {
    if (u == p || u == big_child) continue;
    for (int ps = tin[u]; ps < tout[u]; ps++) {
      int w = euler[ps];
      cnt[h[w]]++;
      upd(h[w]);
    }
  }
  ans[v] = curmaxh - h[v];
  if (flag) {
    for (int ps = tin[v]; ps < tout[v]; ps++) {
      cnt[h[euler[ps]]]--;
    }
    curmaxh = 0, curmaxval = 0;
  }
}
void solve() {
  dfs_sz(1);
  dfs(1);
}
