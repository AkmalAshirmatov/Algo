vector<int> get_primes(int p) {
  vector<int> ans;
  for (int i = 2; i * i <= p; i++) {
    if (p % i == 0) {
      ans.push_back(i); while (p % i == 0) p /= i;
    }
  }
  if (p != 1) ans.push_back(p);
  return ans;
}
bool primitive(int g, int phi, vector<int> primes) {
  for (int p : primes) {
    if (binpow(g, phi/p) == 1) return false;
  }
  return true;
}
void solve() {
  int n; cin >> n;
  vector<int> primes = get_primes(n-1);
  MOD = n;
  int g = 2;
  while (!primitive(g, n-1, primes)) g++;
}
