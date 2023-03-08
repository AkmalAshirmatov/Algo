const int N = 300;
vector<int> edges[N], rev[N];
int l[N], r[N];

void addEdge(int v, int u) {
  edges[v].push_back(u);
  rev[u].push_back(v);
}

int used[N], comp[N];
vector<int> topsort;

void dfs1(int v) {
  used[v] = 1;
  for (int u : edges[v]) {
    if (!used[u]) dfs1(u);
  }
  topsort.push_back(v);
}

void dfs2(int v, int clr) {
  comp[v] = clr;
  for (int u : rev[v]) {
    if (comp[u] == -1) dfs2(u, clr);
  }
}

void solve() {
  int n, m; cin >> n >> m;
  for (int i = 0; i < m; i++) {
    cin >> l[i] >> r[i];
    if (l[i] > r[i]) swap(l[i], r[i]);
  }
  for (int i = 0; i < m; i++) {
    for (int j = i + 1; j < m; j++) {
      if (l[i] == l[j] || r[i] == r[j]) continue;
      if (l[i] < l[j] && r[j] < r[i]) continue;
      if (l[j] < l[i] && r[i] < r[j]) continue;
      if (max(l[i], l[j]) < min(r[i], r[j])) {
        addEdge(i * 2, (j * 2) ^ 1);
        addEdge((i * 2) ^ 1, j * 2);
        addEdge(j * 2, (i * 2) ^ 1);
        addEdge((j * 2) ^ 1, i * 2);
      }
    }
  }
  fill(used, used + 2 * m, 0);
  for (int v = 0; v < 2 * m; v++) {
    if (!used[v]) {
      dfs1(v);
    }
  }
  reverse(all(topsort));
  fill(comp, comp + 2 * m, -1);
  int clr = 0;
  for (int v : topsort) {
    if (comp[v] == -1) {
      dfs2(v, clr++);
    }
  }
  for (int v = 0; v < 2 * m; v++) {
    if (comp[v] == comp[v ^ 1]) {
      cout << "Impossible"; return;
    }
  }
  for (int v = 0; v < 2 * m; v += 2) {
    cout << (comp[v] > comp[v ^ 1] ? "i" : "o");
  }
}
