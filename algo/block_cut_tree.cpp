// https://codeforces.com/contest/962/problem/F

const int N = 100100;
int timer = 1;
int tin[N];
int fup[N];
int cutpoint[N];
vector<pair<int,int> > edges[N];
int memv[N], memu[N];
int used[N];
int ans[N];

vector<int> st;
vector<vector<int> > blocks;

void dfs_cutpoint(int v, int pid = -1) {
  fup[v] = tin[v] = timer++;
  int children = 0;
  for (auto [u, id] : edges[v]) {
    if (id == pid) continue;
    if (!tin[u]) {
      dfs_cutpoint(u, id);
      children++;
      fup[v] = min(fup[v], fup[u]);
      if (tin[v] <= fup[u] && pid != -1) {
        cutpoint[v] = 1;
      }
    } else {
      fup[v] = min(fup[v], tin[u]);
    }
  }
  if (pid == -1 && children > 1) {
    cutpoint[v] = 1;
  }
}

void dfs2(int v, int pid = -1) {
  used[v] = 1;
  for (auto [u, id] : edges[v]) {
    if (id == pid) continue;
    if (!used[u]) {
      st.push_back(id);
      dfs2(u, id);
      if (tin[v] <= fup[u]) {
        vector<int> block;
        while (st.back() != id) {
          block.push_back(st.back()); st.pop_back();
        }
        block.push_back(st.back()); st.pop_back();
        blocks.push_back(block);
      }
    } else if (tin[u] < tin[v]) {
      st.push_back(id);
    }
  }
  if (pid == -1) {
    if (!st.empty()) {
      blocks.push_back(st);
    }
  }
}

void solve() {
  int n, m; cin >> n >> m;
  for (int i = 0; i < m; i++) {
    int v, u; cin >> v >> u;
    edges[v].push_back({u,i}); edges[u].push_back({v,i});
    memv[i] = v, memu[i] = u;
  }
  for (int v = 1; v <= n; v++) {
    if (!tin[v]) {
      dfs_cutpoint(v);
      dfs2(v);
    }
  }
  for (auto block : blocks) {
    set<int> st; for (auto id : block) st.insert(memv[id]), st.insert(memu[id]);
    if (st.size() == block.size()) {
      for (auto id : block) ans[id] = 1;
    }
  }
  cout << count(ans,ans+m,1) << "\n";
  for (int i = 0; i < m; i++) if (ans[i]) cout << i+1 << " ";
}
