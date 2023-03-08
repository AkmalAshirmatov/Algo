const int N = 1e5 + 10, LOG = 21;
vector<int> edges[N];
int sz[N];
int tin[N];
int tout[N];
int timer = 0;
int up[N][LOG];
int nxt[N];
int in[N];

void dfsSize(int v, int p) {
  tin[v] = timer++;
  up[v][0] = p;
  for (int lvl = 1; lvl < LOG; lvl++) {
      up[v][lvl] = up[up[v][lvl - 1]][lvl - 1];
  }
  sz[v] = 1;
  for (int &u : edges[v]) {
    if (u == p)
      continue;
    dfsSize(u, v);
    sz[v] += sz[u];
    if (edges[v][0] == p || sz[u] > sz[edges[v][0]])
      swap(u, edges[v][0]);
  }
  tout[v] = timer++;
}

void dfsHLD(int v, int p) {
  in[v] = timer++;
  for (int u : edges[v]) {
    if (u == p)
      continue;
    nxt[u] = (u == edges[v][0] ? nxt[v] : u);
    dfsHLD(u, v);
  }
}

int getMax(int v, int u, int n) {
  int ans = 0;
  while (nxt[u] != nxt[v]) {
    int head = nxt[u];
    ans = max(ans, segmentTree.get(0, 0, n - 1, in[head], in[u]));
    u = up[head][0];
  }
  ans = max(ans, segmentTree.get(0, 0, n - 1, in[v], in[u]));
  return ans;
}

void solve() {
  int n; cin >> n;
  for (int i = 0; i < n - 1; i++) {
    int v, u; cin >> v >> u;
    edges[v].push_back(u); edges[u].push_back(v);
  }
  dfsSize(1, 1);
  timer = 0;
  // nxt[1] = 1;
  dfsHLD(1, 1);
}

// subtree of  correspond to segment [in_v, out_v)
