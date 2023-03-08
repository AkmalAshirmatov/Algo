const int N = 400010;
vector<pair<int, int> > edges[N];
int used[N];
int bridge[N];
pair<int, int> orientation[N];
int tin[N], fup[N], timer = 0;

void dfs(int v, int p = -1) {
  used[v] = 1;
  tin[v] = fup[v] = timer++;
  for (auto [u, id] : edges[v]) {
    if (u == p) continue;
    if (used[u]) {
      if (tin[u] < tin[v]) {
        orientation[id] = {v,u}; // back-edge
      }
      fup[v] = min(fup[v], tin[u]);
    }
    else {
      orientation[id] = {v,u};
      dfs(u, v);
      fup[v] = min(fup[v], fup[u]);
      if (fup[u] > tin[v]) {
        bridge[id] = 1;
      }
    }
  }
}
