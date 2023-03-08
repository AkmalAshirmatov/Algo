const int LOG = 60;
ll gauss[LOG];

void add(ll myxor) {
  for (int bit = LOG - 1; bit >= 0; bit--) {
    if (!gauss[bit] && (myxor >> bit) & 1) {
      gauss[bit] = myxor; break;
    }
    if ((myxor >> bit) & 1) myxor ^= gauss[bit];
  }
}

ll getMinWithGauss(ll myxor) {
  for (int bit = LOG - 1; bit >= 0; bit--) {
    myxor = min(myxor, myxor ^ gauss[bit]);
  }
  return myxor;
}

// also can change initial values to minimum/maximum possible with gauss basis!
