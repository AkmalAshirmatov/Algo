#include <bits/stdc++.h>
using namespace std;

struct RAT {
  ll p, q;
};

bool isLess(RAT a, RAT b) {
  return a.p * b.q < a.q * b.p;
}

RAT sub(RAT a, RAT b) {
  RAT ans = {a.p * b.q - b.p * a.q, a.q * b.q};
  ll g = __gcd(ans.p, ans.q);
  ans.p /= g;
  ans.q /= g;
  return ans;
}
