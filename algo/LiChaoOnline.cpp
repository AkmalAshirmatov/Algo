const ll INF = 1e18;

struct line{
	ll k, b;
	line() {
		k = 0, b = INF;
	}
	line(ll x, ll y) {
		k = x, b = y;
	}
};

ll eval(line l, ll x) {
	return l.k * x + l.b;
}

struct node{
	node *L, *R;
	line l;
	node() {
		l = line();
		L = nullptr;
		R = nullptr;
	}
	node(line x) {
		l = x;
		L = nullptr;
		R = nullptr;
	}
};

const int MINL = -1e9 - 10, MAXR = 1e9 + 10;

struct Li_chao{
	node * root;
	Li_chao() {
		root = new node();
	}

	node * add(line x, node * root, int tl, int tr) {
		if (root == nullptr) root = new node();
		int tm = (tl + tr) / 2;
		bool mid = eval(x, tm) < eval(root->l, tm);
		bool left = eval(x, tl) < eval(root->l, tl);
		if (mid) swap(x, root->l);
		if (tl == tr - 1) return root;
		if (mid != left){
			root->L = add(x, root->L, tl, tm);
		}
		else{
			root->R = add(x, root->R, tm, tr);
		}
		return root;
	}

	void add(line x) {
		root = add(x, root, MINL, MAXR);
	}

	ll get(int x, node * root, int tl, int tr) {
		if (root == nullptr) return INF;
		if (tl >= x + 1 || tr <= x) return INF;
		if (tl == tr - 1) return eval(root->l, x);
		int tm = (tl + tr) / 2;
		return min(eval(root->l, x), min(get(x, root->L, tl, tm), get(x, root->R, tm, tr)));
	}

	ll get(int x) {
		return get(x, root, MINL, MAXR);
	}
};
