vector<pair<int, ll> > redges[N], nredges[N];
vector<int> edges[N];
int n, m;
ll ans = 0;
vector<int> path, cycle;
int used[N], clr[N];

bool dfs(int v) {
  used[v] = 1;
  path.push_back(v);
  for (int u : edges[v]) {
    if (!used[u]) {
      if (dfs(u)) return true;
    }
    else if (used[u] == 1) {
      while (path.back() != u) {
        cycle.push_back(path.back());
        path.pop_back();
      }
      cycle.push_back(u);
      path.clear();
      return true;
    }
  }
  used[v] = 2;
  path.pop_back();
  return false;
}

void solver() {
  for (int v = 1; v <= n; v++) {
    if (redges[v].empty())
      continue;
    ll mn = 1e18;
    for (auto e : redges[v]) {
      mn = min(mn, e.second);
    }
    for (auto &e : redges[v]) {
      e.second -= mn;
    }
    for (auto &e : redges[v]) {
      if (e.second == 0) {
        edges[e.first].push_back(v);
      }
    }
    ans += mn;
  }
  dfs(1);
  if (*min_element(used + 1, used + 1 + n) != 0) {
    cout << "YES\n" << ans << "\n";
    return;
  }
  cycle.clear(); path.clear(); fill(used + 1, used + 1 + n, 0);
  fill(clr + 1, clr + 1 + n, 0);
  for (int v = 1; v <= n; v++) {
    if (!used[v] && dfs(v)) {
      int k = cycle.size();
      for (auto x : cycle) clr[x] = n - k + 1;
      int free = 1;
      for (int v = 1; v <= n; v++) {
        if (clr[v] != n - k + 1) clr[v] = free++;
      }
      if (free != n - k + 1) exit(-1);
      for (int v = 1; v <= n; v++) {
        for (auto e : redges[v]) {
          int u = e.first; ll w = e.second;
          if (clr[u] == clr[v]) continue;
          nredges[clr[v]].push_back({clr[u], w});
        }
        redges[v].clear();
      }
      n = n - k + 1;
      for (int v = 1; v <= n; v++) {
        swap(redges[v], nredges[v]);
      }
      for (int v = 1; v <= n; v++) {
        edges[v].clear();
      }
      fill(used + 1, used + 1 + n, 0);
      cycle.clear();
      path.clear();
      solver();
      return;
    }
  }
  cout << "NO\n";
}

void solve() {
  cin >> n >> m;
  ll mn = 1e18;
  for (int i = 0; i < m; i++) {
    int v, u; ll c; cin >> v >> u >> c;
    if (v == u) continue;
    if (u == 1) continue;
    redges[u].push_back({v, c});
    mn = min(mn, c);
  }
  for (int v = 1; v <= n; v++) {
    for (auto &e : redges[v]) {
      e.second -= mn;
    }
  }
  ans += mn * (n - 1);
  solver();
}
