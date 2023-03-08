int centroid;
int dfsCentroid(int v, int sz, int p = -1) {
  int mysz = 1;
  for (int u : edges[v]) {
    if (u == p || killed[u]) continue;
    mysz += dfsCentroid(u, sz, v);
  }
  if (centroid == -1 && mysz * 2 >= sz) {
    centroid = v;
  }
  return mysz;
}

void dfsParentSay(int v, int p, int lvl) {
  par[v][lvl] = centroid;
  for (int u : edges[v]) {
    if (u == p || killed[u]) continue;
    h[u][lvl] = h[v][lvl] + 1;
    dfsParentSay(u, v, lvl);
  }
}

void solve() {
  int border = n, lvl = 1;
  while (border) {
    for (int v = 1; v <= n; v++) {
      if (!killed[v] && par[v][lvl] == 0) {
        centroid = -1;
        dfsCentroid(v, border);
        if (centroid == -1) centroid = v;
        choosen[centroid] = lvl;
        dfsParentSay(centroid, centroid, lvl);
        killed[centroid] = 1;
      }
    }
    border /= 2;
    lvl++;
  }
}
