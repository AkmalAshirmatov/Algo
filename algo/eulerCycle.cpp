vector<pair<int, int> > edges[N];
int del[N * N];
pair<int, int> ans[N * N];

void dfs_euler(int v) {
  while (!edges[v].empty()) {
    int u, id; tie(u, id) = edges[v].back(); edges[v].pop_back();
    if (del[id]) continue;
    ans[id] = {v, u};
    del[id] = 1;
    dfs_euler(u);
  }
  vt.push_back(v);
}
// unoriented
