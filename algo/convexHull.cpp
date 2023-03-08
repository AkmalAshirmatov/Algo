struct PT {
  ll x, y, id;
  PT operator-(const PT a) { return {x - a.x, y - a.y}; }
};

bool cmp(PT a, PT b) { return a.x < b.x || a.x == b.x && a.y < b.y; }
ll cross(PT a, PT b) { return a.x * b.y - a.y * b.x; }
bool ccw(PT a, PT b) { return cross(a, b) > 0; }
bool cw(PT a, PT b) { return cross(a, b) < 0; }

vector<PT> convexHull(vector<PT> a) {
  sort(a.begin(), a.end(), cmp);
  int n = a.size();
  vector<PT> up, down;
  PT p1 = a[0], p2 = a[n - 1];
  up.push_back(a[0]); down.push_back(a[0]);
  for (int i = 1; i < n; i++) {
    if (i == n - 1 || ccw(p1 - a[i], p2 - a[i])) {
      int sz = up.size();
      while (sz >= 2 && !ccw(up[sz - 2] - up[sz - 1], a[i] - up[sz - 1]))
        up.pop_back(), sz--;
      up.push_back(a[i]);
    }
    if (i == n - 1 || cw(p1 - a[i], p2 - a[i])) {
      int sz = down.size();
      while (sz >= 2 && !cw(down[sz - 2] - down[sz - 1], a[i] - down[sz - 1]))
        down.pop_back(), sz--;
      down.push_back(a[i]);
    }
  }
  for (int i = up.size() - 2; i >= 1; i--) {
    down.push_back(up[i]);
  }
  return down;
}
