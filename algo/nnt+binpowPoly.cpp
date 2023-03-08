// 998 244 353 can be
const int MOD = 786433;
const int LOG = 17;
const int N = 1 << LOG;
const int NN = N + 2;
const int LIM = 5e4 + 1;
int w[NN];
int binRev[NN];
int REV;

int add(int a, int b) {
  a += b;
  if (a >= MOD) a -= MOD;
  return a;
}
int sub(int a, int b) {
  a -= b;
  if (a < 0) a += MOD;
  return a;
}
int mult(int a, int b) {
  return (1LL * a * b) % MOD;
}
int binpow(int a, int n) {
  int res = 1;
  while (n) {
    if (n & 1)
      res = mult(res, a);
    n >>= 1;
    a = mult(a, a);
  }
  return res;
}

void initFFT() {
  int W = 2;
  while (true) {
    int x = W;
    for (int i = 1; i < LOG; i++) {
      x = mult(x, x);
    }
    if (x == MOD - 1)
    break;
    W++;
  }
  w[0] = 1;
  for (int i = 1; i < N; i++) {
    w[i] = mult(w[i - 1], W);
  }
  for (int mask = 1; mask < N; mask++) {
    binRev[mask] = (binRev[mask >> 1] >> 1) ^ ((mask & 1) << (LOG - 1));
  }
  REV = binpow(N, MOD - 2);
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
        int y = mult(A[st + len + i], w[i << (LOG - 1 - lvl)]);
        A[st + i] = add(x, y);
        A[st + len + i] = sub(x, y);
      }
    }
  }
}

int a[NN], ans[NN], tmp[NN];

void mul(int *A, int *B) {
  FFT(A, LOG);
  if (A != B)
    FFT(B, LOG);
	for (int i = 0; i < N; i++) {
		A[i] = mult(A[i], B[i]);
  }
	FFT(A, LOG);
	reverse(A + 1, A + N);
  for (int i = 0; i < N; i++) {
    A[i] = mult(A[i], REV);
  }
}

void binpowPoly(int k) {
  int flag = -1;
  while (k) {
    if (k & 1) {
      if (flag == -1) {
        for (int i = 0; i < N; i++)
    		  ans[i] = a[i];
        flag = 1;
      }
      else {
        for (int i = 0; i < N; i++)
    		  tmp[i] = a[i];
        mul(ans, tmp);
        for (int i = LIM; i < N; i++)
          ans[i] = 0;
      }
    }
    k >>= 1;
    mul(a, a);
    for (int i = LIM; i < N; i++)
      a[i] = 0;
  }
}

void solve() {
  initFFT();
  int n, k, q; cin >> n >> k >> q;
  for (int i = 0; i < n; i++) {
    int v; cin >> v;
    a[v] = add(a[v], 1);
  }
  binpowPoly(k);
}
