struct node {
  int sum;
  node * left, * right;
  node(): sum(0), left(NULL), right(NULL) {}
};

int sz = 0;
const int N = 3e6;
node t[N];

int getsum(node * & v) {
  return v == NULL ? 0 : v -> sum;
}

void calcsum(node * & v) {
  v -> sum = getsum(v -> left) + getsum(v -> right);
}

node * update(node * v, int tl, int tr, int pos) {
  if (v == NULL) v = t + (sz++);
  if (tl == tr) {
    v -> sum = 1;
  }
  else {
    int tm = (tl + tr) >> 1;
    if (pos <= tm)
      v -> left = update(v -> left, tl, tm, pos);
    else
      v -> right = update(v -> right, tm + 1, tr, pos);
    calcsum(v);
  }
  return v;
}

int get(node * v, int tl, int tr, int k) {
  if (v == NULL) {
    return tl + k - 1;
  }
  else {
    int tm = (tl + tr) >> 1;
    int leftcnt = tm - tl + 1 - getsum(v -> left);
    if (leftcnt >= k)
      return get(v -> left, tl, tm, k);
    else
      return get(v -> right, tm + 1, tr, k - leftcnt);
  }
}

void solve() {
  node * root = NULL;
  int n, m;
  cin >> n >> m;
  for (int i = 0; i < m; i++) {
    char c;
    int v;
    cin >> c >> v;
    int p = get(root, 1, n, v);
    if (c == 'L') cout << p << "\n";
    else root = update(root, 1, n, p);
  }
}



// LAZY PROPAGATION!!!
// https://codeforces.com/problemset/problem/817/F



struct node {
  ll sum;
  char op;
  char inv;
  node * left, * right;
  node(): sum(0), left(NULL), right(NULL) {}
};

int sz = 0;
const int N = 3e7;
node t[N];

ll getsum(node * & v) {
  return v==NULL ? 0 : v->sum;
}

void recalc(node * & v) {
  v->sum = getsum(v->left) + getsum(v->right);
}

void change(node * &v, int op, ll len) {
  if (op == 3) {
    v->inv^=1;
    v->sum = len-v->sum;
  }
  else {
    v->sum = len*(op==1);
    v->op = op;
    v->inv = 0;
  }
}

void push(node * &v, ll tl, ll tm, ll tr) {
  if (v->left == NULL) {
    v->left = t + (sz++);
  }
  if (v->right == NULL) {
    v->right = t + (sz++);
  }
  if (sz >= N) {
    cout << "NO"; exit(0);
  }
  if (v->op != 0) {
    change(v->left, v->op, tm-tl+1);
    change(v->right, v->op, tr-tm);
    v->op = 0;
  }
  if (v->inv != 0) {
    change(v->left, 3, tm-tl+1);
    change(v->right, 3, tr-tm);
    v->inv = 0;
  }
}

void update(node * &v, ll tl, ll tr, ll l, ll r, int op) {
  if (tl == l && tr == r) {
    change(v, op, tr-tl+1);
  }
  else {
    ll tm = (tl + tr) >> 1;
    push(v, tl, tm, tr);
    if (l <= min(r, tm)) {
      update(v->left, tl, tm, l, min(r, tm), op);
    }
    if (max(l,tm+1) <= r) {
      update(v->right, tm+1, tr, max(l,tm+1), r, op);
    }
    recalc(v);
  }
}

ll get(node *&v, ll tl, ll tr) {
  if (tl == tr) {
    return tl;
  }
  ll tm = (tl + tr) >> 1;
  push(v, tl, tm, tr);
  if (v->left->sum == tm-tl+1)
    return get(v->right, tm+1, tr);
  else
    return get(v->left, tl, tm);
}

ll TL = 1, TR = ll(1e18)+2;

void solve() {
  node *root = t + (sz++);
  int n; cin >> n;
  while (n--) {
    ll t, l, r; cin >> t >> l >> r;
    update(root, TL, TR, l, r, t);
    cout << get(root, TL, TR) << "\n";
  }
}
