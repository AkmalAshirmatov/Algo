vector<pair<int, ll> > redges[N], nredges[N];
int n, m;
ll ans = 0;
int used[N], clr[N];
vector<int> order, sccedges[N], rsccedges[N];

void dfs1(int v) {
  used[v] = 1;
  for (int u : sccedges[v]) {
    if (!used[u])
      dfs1(u);
  }
  order.push_back(v);
}

void dfs2(int v, int c) {
  used[v] = 1;
  clr[v] = c;
  for (int u : rsccedges[v]) {
    if (!used[u])
      dfs2(u, c);
  }
}

void solver(int root) {
  for (int v = 0; v < n; v++) {
    sccedges[v].clear(); rsccedges[v].clear();
  }
  for (int v = 0; v < n; v++) {
    if (v == root || redges[v].empty())
      continue;
    ll mn = 1e18;
    for (auto e : redges[v]) {
      mn = min(mn, e.second);
    }
    for (auto &e : redges[v]) {
      e.second -= mn;
      if (e.second == 0) {
        sccedges[e.first].push_back(v);
        rsccedges[v].push_back(e.first);
      }
    }
    ans += mn;
  }
  fill(used, used + n, 0);
  order.clear();
  dfs1(root);
  if (*min_element(used, used + n) != 0) {
    cout << "YES\n" << ans << "\n"; return;
  }
  for (int v = 0; v < n; v++) {
    if (!used[v])
      dfs1(v);
  }
  reverse(all(order));
  fill(used, used + n, 0);
  int free = 0;
  for (auto v : order) {
    if (!used[v]) {
      dfs2(v, free++);
    }
  }
  if (free == n) {
    cout << "NO\n"; return;
  }
  for (int v = 0; v < n; v++) {
    for (auto e : redges[v]) {
      int u = e.first; ll w = e.second;
      if (clr[v] == clr[u]) continue;
      nredges[clr[v]].push_back({clr[u], w});
    }
    redges[v].clear();
  }
  n = free;
  for (int v = 0; v < n; v++) {
    swap(redges[v], nredges[v]);
  }
  solver(clr[root]);
}

void solve() {
  cin >> n >> m;
  ll mn = 1e18;
  for (int i = 0; i < m; i++) {
    int v, u; ll c; cin >> v >> u >> c; v--, u--;
    if (v == u) continue;
    redges[u].push_back({v, c});
    mn = min(mn, c);
  }
  for (int v = 0; v < n; v++) {
    for (auto &e : redges[v]) {
      e.second -= mn;
    }
  }
  ans += (n - 1) * 1LL * mn;
  solver(0);
}
