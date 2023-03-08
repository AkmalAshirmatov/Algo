vector<int> topsort;
vector<int> edges[N], revedges[N], nedges[N];
int used[N], clr[N], sz[N];

void dfs(int v) {
  used[v] = 1;
  for (int u : edges[v]) {
    if (!used[u]) dfs(u);
  }
  topsort.push_back(v);
}

void dfs2(int v, int get) {
  clr[v] = get;
  sz[get]++;
  for (int u : revedges[v]) {
    if (!clr[u]) {
      dfs2(u, get);
    }
  }
}

void dfs3(int v) {
  used[v] = 1;
  for (int u : nedges[v]) {
    if (!used[u]) dfs3(u);
  }
  topsort.push_back(v);
}

void solve() {
  int n, m; cin >> n >> m;
  for (int i = 0; i < m; i++) {
    int v, u; cin >> v >> u; edges[v].push_back(u); revedges[u].push_back(v);
  }
  for (int v = 1; v <= n; v++) {
    if (!used[v]) dfs(v);
  }
  reverse(all(topsort));
  int timer = 1;
  for (auto v : topsort) {
    if (!clr[v]) {
      dfs2(v, timer++);
    }
  }
  topsort.clear();
  for (int v = 1; v <= n; v++) {
    for (int u : edges[v]) {
      if (clr[v] != clr[u]) {
        nedges[clr[v]].push_back(clr[u]);
      }
    }
  }
  fill(used + 1, used + 1 + timer, 0);
  for (int v = 1; v < timer; v++) {
    if (!used[v]) {
      dfs3(v);
    }
  }
  reverse(all(topsort));
  fill(used + 1, used + 1 + timer, 0);
  dfs3(topsort[0]);
  int flag = 1;
  for (int v = 1; v < timer; v++) {
    if (!used[v]) {
      flag = 0;
    }
  }
  if (flag) {
    cout << sz[topsort[0]] << "\n";
    for (int v = 1; v <= n; v++) {
      if (clr[v] == topsort[0]) {
        cout << v << " ";
      }
    }
  }
  else {
    cout << 0;
  }
}
