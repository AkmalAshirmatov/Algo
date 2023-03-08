const int BSZ = 250;

struct QR {
  int l, r, id;
};

void add(int pos, int delta) {
  sum -= cnt[a[pos]] * cnt[a[pos]] * a[pos];
  cnt[a[pos]] += delta;
  sum += cnt[a[pos]] * cnt[a[pos]] * a[pos];
}

void solve() {
  int n, q; cin >> n >> q;
  for (int i = 0; i < n; i++) {
    cin >> a[i];
  }
  vector<QR> qr;
  for (int i = 0; i < q; i++) {
    int l, r; cin >> l >> r; l--, r--;
    r++;
    qr.push_back({l, r, i});
  }
  sort(all(qr), [&](const QR &a, const QR &b)
  {
    if (a.l / BSZ != b.l / BSZ) return a.l / BSZ < b.l / BSZ;
    if (a.r == b.r) return false;
    return (bool)(((a.l / BSZ) % 2 == 1) ^ (a.r < b.r)); // для четного слева направо, для нечетного наоборот
  });
  int cl = 0;
  int cr = 0;
  for (auto q : qr) {
    while (cr < q.r) add(cr++, 1);
    while (cl > q.l) add(--cl, 1);
    while (cr > q.r) add(--cr, -1);
    while (cl < q.l) add(cl++, -1);
    ans[q.id] = sum;
  }
  for (int i = 0; i < q; i++) {
    cout << ans[i] << "\n";
  }
}
