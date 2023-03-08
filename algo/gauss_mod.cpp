void gauss(vector<vector<int> > &vt) {
  int n = vt.size(), m = vt[0].size();
  for (int i = 0; i < n; i++) {
    int _inv = inv(vt[i][i]);
    for (int j = 0; j < m; j++) {
      vt[i][j] = mul(vt[i][j], _inv);
    }
    for (int ni = 0; ni < n; ni++) {
      if (i == ni) continue;
      int mult = vt[ni][i];
      for (int j = 0; j < m; j++) {
        add(vt[ni][j], -mul(mult, vt[i][j]));
      }
    }
  }
}
