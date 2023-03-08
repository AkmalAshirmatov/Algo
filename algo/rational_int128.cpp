struct fraction{
    __int128 ch, zn;
    fraction(__int128 a, __int128 n) : ch(a), zn(n){}
    fraction(__int128 a) : ch(a), zn(1){}
    fraction() : ch(0), zn(1){}

    fraction operator + (const fraction &a) const{
      fraction tmp = fraction(ch * a.zn + a.ch * zn, zn * a.zn);
      if (tmp.ch == 0 && tmp.zn == 0) return tmp;
      __int128 g = __gcd(tmp.ch, tmp.zn);
      tmp.ch /= g; tmp.zn /= g;
      return tmp;
    }
    fraction operator - (const fraction &a) const{
      fraction tmp = fraction(ch * a.zn - a.ch * zn, zn * a.zn);
      if (tmp.ch == 0 && tmp.zn == 0) return tmp;
      __int128 g = __gcd(tmp.ch, tmp.zn);
      if (g < 0) g *= -1;
      tmp.ch /= g; tmp.zn /= g;
      return tmp;
    }
    fraction operator * (const fraction &a) const{
      fraction tmp = fraction(ch * a.ch, zn * a.zn);
      if (tmp.ch == 0 && tmp.zn == 0) return tmp;
      __int128 g = __gcd(tmp.ch, tmp.zn);
      tmp.ch /= g; tmp.zn /= g;
      return tmp;
    }
    fraction operator / (const fraction &a) const{
      __int128 p = ch; p *= a.zn;
      __int128 q = zn; q *= a.ch;
      __int128 g = __gcd(p, q);
      p /= g, q /= g;
      return fraction(p, q);
    }
};

void print(__int128 a) {
  if (a == 0) {
    cout << 0; return;
  }
  vector<int> rem;
  while (a) {
    rem.push_back(a % 10); a /= 10;
  }
  reverse(all(rem)); for (auto x : rem) cout << x;
}
