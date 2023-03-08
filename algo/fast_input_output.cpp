inline int FastI() {
	bool minus = false;
	int result = 0;
	char ch;
	ch = getchar();
	while (true) {
		if (ch == '-') break;
		if (ch >= '0' && ch <= '9') break;
		ch = getchar();
	}
	if (ch == '-') minus = true; else result = ch-'0';
	while (true) {
		ch = getchar();
		if (ch < '0' || ch > '9') break;
		result = result*10 + (ch - '0');
	}
  return (minus ? -result : result);
}

inline void FastO(int val) {
  bool c = 0;
  for (int i = 1000000000; i >= 1; i /= 10) {
    if (val / i) {
      c = 1;
      _putc_nolock(val / i + '0', stdout);
      val %= i;
    }
    else if (c) _putc_nolock('0', stdout);
  }
  if (!c) _putc_nolock('0', stdout);
  _putc_nolock('\n', stdout);
}

inline void FastO(ll val) {
  bool c = 0;
  for (ll i = 1000000000000000ll; i >= 1; i /= 10) {
    if (val / i) {
      c = 1;
      _putc_nolock(val / i + '0', stdout);
      val %= i;
    }
    else if (c) _putc_nolock('0', stdout);
  }
  if (!c) _putc_nolock('0', stdout);
  _putc_nolock('\n', stdout);
}
