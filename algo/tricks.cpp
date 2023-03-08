// TRICKS WITH OPERATOR NEW
// 200 mb
const int MAX_MEM=2e8;
int mpos=0;
char mem[MAX_MEM];
inline void* operator new(size_t n) {
  char*res=mem+mpos;
  mpos+=n;
  assert(mpos<=MAX_MEM);
  return(void*)res;
}
inline void operator delete(void*) { }

// SPEED UP unordered_map
unordered_map<int, int> mp
mp.max_load_factor(0.25);
mp.reserve(1000);

// pragmas
#pragma GCC target ("avx2")
#pragma GCC optimization ("O3")
#pragma GCC optimization ("unroll-loops»)
// OR
#pragma GCC optimize("O3")
#pragma GCC target("sse,sse2,sse3,ssse3,sse4,popcnt,abm,mmx")

// FIND FIRST BIT
int bit = 63 - __builtin_clzll(x);
int bit = 31 - __builtin_clz(x);

// BITSET
for (int bit = bt._Find_first(); bit < bt.size(); bit = bt._Find_next(bit)) { }

// GRAY
int g (int n) {
	return n ^ (n >> 1);
}
int rev_g (int g) {
	int n = 0;
	for (; g; g>>=1)
		n ^= g;
	return n;
}

// merge
merge (t[v*2].begin(), t[v*2].end(), t[v*2+1].begin(), t[v*2+1].end(),
			back_inserter (t[v]));


mt19937_64 rnd(time(NULL));
mt19937 rnd(time(0));
mt19937 rng(chrono::steady_clock::now().time_since_epoch().count());

ostream& operator<<(ostream& cout, const __int128 &b) {
  __int128 a = b;
  if (a == 0) {
    cout << "0"; return cout;
  }
  vector<int> rem;
  while (a) {
    rem.push_back(a % 10); a /= 10;
  }
  reverse(all(rem)); for (auto x : rem) cout << x;
  return cout;
}

// sqrt(n)
for (ll l = 1; l <= n; ) {
  ll k = n/l;
  ll r = n/k;
  // ...
  l = r+1;
}
