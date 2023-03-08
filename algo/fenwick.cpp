struct Fenwick {
  ll ft[N];
  ll sum(int r) {
    ll result = 0;
    for (; r >= 0; r = (r & (r + 1)) - 1)
      result += ft[r];
    return result;
  }
  ll sum(int l, int r) {
    return (l > r ? 0ll : sum(r) - sum(l - 1));
  }
  void inc(int i, ll delta) {
    for (; i < N; i = (i | (i + 1)))
      ft[i] += delta;
  }
};
struct Fenwick2d {
  ll ft[N][N];
  ll sum(int x, int y) {
    ll result = 0;
    for (int i = x; i >= 0; i = (i & (i+1)) - 1) {
      for (int j = y; j >= 0; j = (j & (j+1)) - 1) {
        result ^= ft[i][j];
      }
    }
    return result;
  }
  void inc(int x, int y, ll delta) {
    for (int i = x; i < N; i = (i | (i+1))) {
      for (int j = y; j < N; j = (j | (j+1))) {
        ft[i][j] ^= delta;
      }
    }
  }
};
