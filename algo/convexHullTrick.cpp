double ptIntersect(pair <ll, ll>  a, pair <ll, ll> b){
  return (b.second - a.second) * 1.0 / (double)(a.first - b.first);
}

void scan() {
  for (int i = 0; i < n; j++){
    hm.push_back({x, y});
  }
}

void buildULowerConvexHull() {
  for (auto ln : pr){
    if (lowerConvexHull.size() > 0 && lowerConvexHull.back().first == ln.first) continue; // parallel!!!
    while (lowerConvexHull.size() >= 2 && ptIntersect(lowerConvexHull[lowerConvexHull.size() - 2], lowerConvexHull.back()) >= ptIntersect(lowerConvexHull.back(), ln)) lowerConvexHull.pop_back();
    lowerConvexHull.push_back(p);
  }
}

void addLine(pair<ll, ll> ln) {
  while (lowerConvexHull.size() >= 2 && ptIntersect(lowerConvexHull[lowerConvexHull.size() - 2], lowerConvexHull.back()) >= ptIntersect(lowerConvexHull.back(), ln)) lowerConvexHull.pop_back();
  lowerConvexHull.push_back(ln);
}

ll findMin(ll x) {
  int l = 1, r = lowerConvexHull.size() - 1, need = 0;
  while (l <= r) {
    int m = (l + r) >> 1;
    if (ptIntersect(lowerConvexHull[m - 1], lowerConvexHull[m]) <= x)
      l = m + 1, need = m;
    else
      r = m - 1;
  }
  return lowerConvexHull[need].first * x + lowerConvexHull[need].second;
}

void solve() {
  vector <pair <ll, ll> > pr;
  scan();
  sort(pr.begin(), pr.end());
  buildUpperConvexHull();
  int y = findValue(x);
}

// https://codeforces.com/problemset/problem/319/C


deque<pair<ll, ll> > upperConvexHull;

void addLine(pair<ll, ll> ln) {
  while (upperConvexHull.size() >= 2 &&
          ptIntersect(upperConvexHull[0], upperConvexHull[1]) <=
          ptIntersect(upperConvexHull[0], ln)) upperConvexHull.pop_front();
  upperConvexHull.push_front(ln);
}

ll findMax(ll x) {
  int l = 1, r = upperConvexHull.size() - 1, need = 0;
  while (l <= r) {
    int m = (l + r) >> 1;
    if (ptIntersect(upperConvexHull[m - 1], upperConvexHull[m]) <= x)
      l = m + 1, need = m;
    else
      r = m - 1;
  }
  return upperConvexHull[need].first * x + upperConvexHull[need].second;
}

sort(p, p+n, [&](int i, int j) {
  return x[i] < x[j];
});
for (int iter = 0; iter < n; iter++) {
  int i = p[iter];
  addLine({-x[i], dp});
}
