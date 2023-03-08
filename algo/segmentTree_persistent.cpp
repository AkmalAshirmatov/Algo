struct node {
	node *l, *r;
	ll sum;

	node() {
		l = NULL, r = NULL, sum = 0;
	}
	node(int _val) {
		l = NULL, r = NULL, sum = _sum;
	}
	node(node *_l, node *_r) {
		l = _l, r = _r, sum = 0;
	}
};

node *build(int tl, int tr) {
	if (tl == tr) {
		return new node(0ll);
	}
	int tm = (tl + tr) >> 1;
	return new node(build(tl, tm), build(tm+1, tr));
}

int get_sum(node *t, int tl, int tr, int l, int r) {
	if (l > r)
		return 0;
	if (l == tl && tr == r)
		return t->sum;
	int tm = (tl + tr) >> 1;
	return get_sum(t->l, tl, tm, l, min(r,tm))
		+ get_sum (t->r, tm+1, tr, max(l,tm+1), r);
}

node *update(node *t, int tl, int tr, int pos, ll new_val) {
	if (tl == tr) {
		return new node(new_val);
	}
	int tm = (tl + tr) >> 1;
	node *root;
	if (pos <= tm) {
		root = new node(update(t->l, tl, tm, pos, new_val), t->r);
	}
	else {
		root = new node(t->l, update(t->r, tm+1, tr, pos, new_val));
	}
	root->sum = root->l->sum + root->r->sum;
	return root;
}

node *root = build(1, n);
