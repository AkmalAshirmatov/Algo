vector<int> edges[N];
int depth[N];
int up[N][LOG];

void dfs(int v, int p) {
  up[v][0] = p;
  for (int lvl = 1; lvl < LOG; lvl++) {
    up[v][lvl] = up[up[v][lvl - 1]][lvl - 1];
  }
  for (int u : edges[v]) {
    if (u == p) continue;
    depth[u] = depth[v] + 1;
    dfs(u, v);
  }
}
int go(int v, int length) {
  for (int lvl = 0; lvl < LOG; lvl++) {
    if (length & (1 << lvl))
      v = up[v][lvl];
  }
  return v;
}
int lca(int a, int b) {
  if (depth[a] > depth[b]) swap(a, b);
  b = go(b, depth[b] - depth[a]);
  if (a == b) return a;
  for (int lvl = LOG - 1; lvl >= 0; lvl--) {
    if (up[a][lvl] != up[b][lvl])
      a = up[a][lvl], b = up[b][lvl];
  }
  return up[a][0];
}

void solve() {
  int n, m; cin >> n >> m;
  for (int i = 0; i < n - 1; i++) {
    int v, u; cin >> v >> u;
    v--, u--;
    edges[v].push_back(u); edges[u].push_back(v);
  }
  dfs(0, 0);
}






void dfs(int v, int p, int pw) {
  up[v][0] = p; mx[v][0] = pw;
  for (int lvl = 1; lvl < LOG; lvl++) {
    up[v][lvl] = up[up[v][lvl - 1]][lvl - 1];
    mx[v][lvl] = max(mx[v][lvl - 1], mx[up[v][lvl - 1]][lvl - 1]);
  }
  for (auto [u, w] : edges[v]) {
    if (u == p) continue;
    depth[u] = depth[v] + 1;
    dfs(u, v, w);
  }
}

pair<int, int> go(int v, int length) {
  int res = 0;
  for (int lvl = 0; lvl < LOG; lvl++) {
    if (length & (1 << lvl))
      res = max(res, mx[v][lvl]), v = up[v][lvl];
  }
  return {v, res};
}

int ans(int a, int b) {
  if (depth[a] > depth[b]) swap(a, b);
  auto g = go(b, depth[b] - depth[a]);
  b = g.first;
  if (a == b) return g.second;
  int res = g.second;
  for (int lvl = LOG - 1; lvl >= 0; lvl--) {
    if (up[a][lvl] != up[b][lvl])
      res = max(res, max(mx[a][lvl], mx[b][lvl])), a = up[a][lvl], b = up[b][lvl];
  }
  res = max(res, max(mx[a][0], mx[b][0]));
  return res;
}
