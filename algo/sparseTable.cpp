struct SparseTable {
  int sp[N][LOG];
  int plen[N];

  void init(vector<int> a) {
    int n = a.size();
    for (int i = 0; i < n; i++) {
      sp[i][0] = a[i];
    }
    for (int i = 2; i <= n; i++) {
      plen[i] = plen[i / 2] + 1;
    }
    for (int lvl = 1; lvl < LOG; lvl++) {
      for (int i = 0; i + (1 << lvl) - 1 < n; i++) {
        sp[i][lvl] = min(sp[i][lvl - 1], sp[i + (1 << (lvl - 1))][lvl - 1]);
      }
    }
  }

  int getmin(int l, int r) {
    int len = plen[r - l + 1];
    return min(sp[l][len], sp[r - (1 << len) + 1][len]);
  }
};
