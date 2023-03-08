const int N = 7600;
vector<int> edges[N];
int deg[N];

void solve() {
  int n;
  vector<int> p;
  while (cin >> n) {
    deg[n]++;
    p.push_back(n);
  }
  n = p.size() + 2;
  for (int v = 1; v <= n; v++) {
    deg[v]++;
  }
  set<int> st;
  for (int v = 1; v <= n; v++) {
    if (deg[v] == 1)
      st.insert(v);
  }
  for (int i = 0; i < n - 2; i++) {
    int v = *st.begin();
    st.erase(st.begin());
    edges[v].push_back(p[i]); edges[p[i]].push_back(v);
    deg[p[i]]--; deg[v]--;
    if (deg[p[i]] == 1) {
      st.insert(p[i]);
    }
  }
  int u = -1;
  for (int v = 1; v <= n; v++) {
    if (deg[v] == 1) {
      if (u == -1)
        u = v;
      else
        edges[v].push_back(u), edges[u].push_back(v);
    }
  }
  for (int v = 1; v <= n; v++) {
    cout << v << ": ";
    sort(edges[v].begin(), edges[v].end());
    for (auto x : edges[v])
      cout << x << " ";
    cout << "\n";
  }
}
