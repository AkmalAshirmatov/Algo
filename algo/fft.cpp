typedef complex<double> cd;
const int LOG = 20;
const int N = 1 << LOG;
const int NN = N + 2;
const double PI = acos(-1.0);
int rev[NN];
cd w[NN];
void initFFT() {
  for (int i = 0; i < N; i++) {
    w[i] = cd(cos(2 * PI * i / N), sin(2 * PI * i / N));
  }
  rev[0] = 0;
  for (int mask = 1; mask < N; mask++) {
    rev[mask] = (rev[mask >> 1] >> 1) | ((mask & 1) << (LOG - 1));
  }
}
void FFT(cd* a, int k) {
  int L = 1 << k;
  for (int i = 0; i < L; i++) {
    int x = rev[i] >> (LOG - k);
    if (i < x)
      swap(a[i], a[x]);
  }
  for (int lvl = 0; lvl < k; lvl++) {
    int blsize = 1 << lvl;
    for (int sb = 0; sb < L; sb += (blsize << 1)) {
      for (int i = 0; i < blsize; i++) {
        cd x = a[sb + i];
        cd y = a[sb + i + blsize] * w[i << (LOG - 1 - lvl)];
        a[sb + i] = x + y;
        a[sb + i + blsize] = x - y;
      }
    }
  }
}
cd a[N], b[N];
void solve() {
  initFFT();
  int k = LOG;
  for (int i = 0; i < 3; i++) {
    a[i] = b[i] = cd(1, 0);
  }
  FFT(a, k);
  FFT(b, k);
  for (int i = 0; i < (1 << k); i++) {
    a[i] = a[i] * b[i];
  }
  FFT(a, k);
  reverse(a + 1, a + (1 << k));
  for (int i = 0; i < 10; i++) {
    ll(round(a[i].real() / double((1 << k))))
    cout << int(a[i].real() / double((1 << k)) + 1e-9) << " ";
  }
}
