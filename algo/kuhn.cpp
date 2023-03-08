//https://acm.timus.ru/problem.aspx?space=1&num=1997

const int N = 1e4;

vector<int> edges[N];
int used[N];
int mt[N];
int mtleft[N];

bool kuhn(int v) {
  if (used[v])
    return false;
  used[v] = 1;
  for (auto u : edges[v]) {
    if (mt[u] == -1) {
      mt[u] = v;
      mtleft[v] = u;
      return true;
    }
  }
  for (auto u : edges[v]) {
    if (kuhn(mt[u])) {
      mt[u] = v;
      mtleft[v] = u;
      return true;
    }
  }
  return false;
}

void solve() {
  edges[left].push_back(right);
  int lft = cp.size();
  int rgt = n;
  fill(mtleft, mtleft + lft, -1);
  fill(mt, mt + rgt, -1);
  int mm = 0, run = 1;
  while (run && mm != rgt) {
    run = 0;
    fill(used, used + lft, 0);
    for (int i = 0; i < lft; i++)
      if (mtleft[i] == -1 && kuhn(i))
        run = 1, mm++;
  }
  if (mm != rgt) {
      cout << "No solution";
  }
  else {
    for (int i = 0; i < rgt; i++) {
      cout << cp[mt[i]] << "\n";
    }
  }
}
