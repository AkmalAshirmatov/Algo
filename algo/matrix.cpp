struct Matrix {
  int n, m;
  vector<vector<int> > vt;

  void init(int n, int m) {
    this->n = n;
    this->m = m;
    vt = vector<vector<int> >(n, vector<int>(m, 0));
  }

  void unitMatrix() {
    for (int i = 0; i < min(n, m); i++)
      vt[i][i] = 1;
  }

  void print() {
    for (int i = 0; i < n; i++) {
      for (int j = 0; j < m; j++) {
        cout << vt[i][j] << " ";
      }
      cout << endl;
    }
  }
};

Matrix mul(Matrix a, Matrix b) {
  Matrix res;
  res.init(a.n, b.m);
  for (int i = 0; i < a.n; i++) {
    for (int j = 0; j < b.m; j++) {
      for (int k = 0; k < a.m; k++) { //a.m = b.n
        add(res.vt[i][j], mul(a.vt[i][k], b.vt[k][j]));
      }
    }
  }
  return res;
}

Matrix binpow(Matrix a, int sz, ll n) {
  Matrix res;
  res.init(sz, sz);
  res.unitMatrix();
  while (n) {
    if (n & 1) {
      res = mul(res, a);
    }
    a = mul(a, a);
    n >>= 1;
  }
  return res;
}
