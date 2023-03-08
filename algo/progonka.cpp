vector<double> progonka(int n, vector<double> a, vector<double> b, vector<double> c, vector<double> d) {
  vector<double> p(n), q(n);
  p[0] = -c[0] / b[0]; q[0] = d[0] / b[0];
  for (int i = 1; i < n; i++) {
    p[i] = -c[i] / (a[i]*p[i-1] + b[i]);
    q[i] = (d[i] - a[i]*q[i-1]) / (a[i]*p[i-1] + b[i]);
  }
  vector<double> ans(n);
  ans[n-1] = q[n-1];
  for (int i = n-2; i >= 0; i--) {
    ans[i] = p[i]*ans[i+1] + q[i];
  }
  return ans;
}
