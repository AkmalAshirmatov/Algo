// 786433
const int MOD = 998244353;
const int LOG = 20;
const int N = 1 << LOG;
const int NN = N + 2;
const int LIM = 5e4 + 1;
int w[NN];
int binRev[NN];
int REV;

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

void initFFT() {
  int W = 2;
  while (true) {
    int x = W;
    for (int i = 1; i < LOG; i++) {
      x = mul(x, x);
    }
    if (x == MOD - 1)
    break;
    W++;
  }
  w[0] = 1;
  for (int i = 1; i < N; i++) {
    w[i] = mul(w[i - 1], W);
  }
  for (int mask = 1; mask < N; mask++) {
    binRev[mask] = (binRev[mask >> 1] >> 1) ^ ((mask & 1) << (LOG - 1));
  }
  REV = inv(N);
}

void FFT(int* A, int k) {
  int L = 1 << k;
  for (int i = 0; i < L; i++) {
    int x = binRev[i] >> (LOG - k);
    if (i < x)
      swap(A[i], A[x]);
  }
  for (int lvl = 0; lvl < k; lvl++) {
    int len = 1 << lvl;
    for (int st = 0; st < L; st += (len << 1)) {
      for (int i = 0; i < len; i++) {
        int x = A[st + i];
        int y = mul(A[st + len + i], w[i << (LOG - 1 - lvl)]);
        A[st + i] = x;
        add(A[st + i], y);
        A[st + len + i] = x;
        add(A[st + len + i], -y);
      }
    }
  }
}

void mul(int *A, int *B) {
  FFT(A, LOG);
  if (A != B)
    FFT(B, LOG);
	for (int i = 0; i < N; i++) {
		A[i] = mul(A[i], B[i]);
  }
	FFT(A, LOG);
	reverse(A + 1, A + N);
  for (int i = 0; i < N; i++) {
    A[i] = mul(A[i], REV);
  }
}

int a[N], b[N];

void solve() {
  initFFT();
  int k = LOG;
  for (int i = 0; i < 3; i++) {
    a[i] = b[i] = 1;
  }
  FFT(a, k);
  FFT(b, k);
  for (int i = 0; i < (1 << k); i++) {
    a[i] = mul(a[i], b[i]);
  }
  FFT(a, k);
  reverse(a + 1, a + (1 << k));
  for (int i = 0; i < 10; i++) {
    a[i] = mul(a[i], REV);
    cout << a[i] << " ";
  }
}

// https://codeforces.com/contest/1218/problem/E segment tree
