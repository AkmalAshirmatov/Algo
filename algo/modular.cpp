const int MOD = 1e9 + 7;
void add(int &x, int y) {
  x += y;
  if (x >= MOD) x -= MOD;
  if (x < 0) x += MOD;
}
int mul(int a, int b) {
  return (a * 1LL * b) % MOD;
}
int binpow(int a, ll n) {
  int res = 1;
  while (n) {
    if (n & 1)
      res = mul(res, a);
    a = mul(a, a); n >>= 1;
  }
  return res;
}
int inv(int a) {
  return binpow(a, MOD - 2);
}
int fact[N], invfact[N];
int cnk(int n, int k) {
  return mul(fact[n], mul(invfact[k], invfact[n - k]));
}
int cat(int n) {
  int ans = cnk(2*n, n); add(ans, -cnk(2*n, n-1)); return ans;
}
int convcat(int k, int n) {
  int ans = cnk(2*n+k, n); add(ans, -cnk(2*n+k, n-1)); return ans;
}

fact[0] = 1;
for (int i = 1; i < N; i++) {
  fact[i] = mul(fact[i - 1], i);
}
invfact[N - 1] = inv(fact[N - 1]);
for (int i = N - 2; i >= 0; i--) {
  invfact[i] = mul(invfact[i + 1], i + 1);
}

c[0][0] = 1;
for (int i = 1; i < N; i++) {
  c[i][0] = 1;
  for (int j = 1; j <= i; j++) {
    c[i][j] = c[i - 1][j]; add(c[i][j], c[i - 1][j - 1]);
  }
}

r[1] = 1;
for (int i=2; i<m; ++i)
	r[i] = (m - (m/i) * r[m%i] % m) % m;

big MODULO
ll mult(ll x, ll y) {
  if (y == 0) return 0;
  return (mult((x * 2) % MOD, y / 2) + x * (y % 2)) % MOD;
}

c[0][0] = 1;
for (int i = 1; i < N; i++) {
  c[i][0] = 1;
  for (int j = 1; j <= i; j++) {
    c[i][j] = c[i - 1][j]; add(c[i][j], c[i - 1][j - 1]);
  }
}
