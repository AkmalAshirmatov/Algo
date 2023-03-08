int MOD;
void add(int &x, int y) {
  x += y;
  if (x >= MOD) x -= MOD;
  if (x < 0) x += MOD;
}
int mul(int a, int b) {
  return (a * 1LL * b) % MOD;
}

struct HASHER {
  int _MOD;
  vector<int> hs;
  vector<int> pw_p;

  HASHER() { }
  
  HASHER(string s, int _MOD, int P) {
    this->_MOD = _MOD;
    MOD = _MOD;
    int n = s.size();
    hs = vector<int>(n + 1);
    for (int i = n - 1; i >= 0; i--) {
      hs[i] = mul(P, hs[i + 1]);
      add(hs[i], s[i] - 'a' + 3);
    }
    pw_p = vector<int>(n + 1);
    pw_p[0] = 1;
    for (int i = 1; i <= n; i++) {
      pw_p[i] = mul(pw_p[i - 1], P);
    }
  }

  int get(int l, int r) {
    MOD = _MOD;
    int ans = hs[l];
    add(ans, -mul(hs[r + 1], pw_p[r - l + 1]));
    return ans;
  }
};

HASHER hasher1(s, 1e9 + 7, 31), hasher2(s, 1e9 + 9, 37);



struct HASHER {
  int _MOD;
  int n;
  vector<int> hs;
  vector<int> pw_inv_p;

  HASHER() { }

  HASHER(string s, int _MOD, int P) {
    this->_MOD = _MOD;
    MOD = _MOD;
    n = s.size();
    hs = vector<int>(n + 1);
    int multp = 1;
    for (int i = n-1; i >= 0; i--) {
      add(hs[i], mul(multp, s[i] - '0'));
      add(hs[i], hs[i+1]);
      multp = mul(multp, P);
    }
    pw_inv_p = vector<int>(n + 1);
    pw_inv_p[0] = 1, pw_inv_p[1] = inv(P);
    for (int i = 2; i <= n; i++) {
      pw_inv_p[i] = mul(pw_inv_p[i - 1], pw_inv_p[1]);
    }
  }

  int get(int l, int r) {
    MOD = _MOD;
    int ans = hs[l]; add(ans, -hs[r+1]);
    ans = mul(ans, pw_inv_p[n-(r+1)]);
    return ans;
  }
};

hasher[0] = HASHER(s, 1000000007, 10);
hasher[1] = HASHER(s, 1000000009, 10);
hasher[2] = HASHER(s, 1000000021, 10);
