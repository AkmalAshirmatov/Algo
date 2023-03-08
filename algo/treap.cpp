mt19937 rnd(time(0));
mt19937 rng(chrono::steady_clock::now().
time_since_epoch().count());

struct vertex {
	int key, prior;
	vertex *l, *r;
	vertex(int key, int prior) : key(key), prior(prior), l(NULL), r(NULL) { }
};

void split(vertex* t, int key, vertex* &l, vertex* &r) {
	if (!t)
		l = r = NULL;
	else if (key < t->key)
		split(t->l, key, l, t->l),  r = t;
	else
		split(t->r, key, t->r, r),  l = t;
}

void insert(vertex* &t, vertex* it) {
	if (!t)
		t = it;
	else if (it->prior > t->prior)
		split(t, it->key, it->l, it->r), t = it;
	else
		insert(it->key < t->key ? t->l : t->r, it);
}

void merge(vertex* &t, vertex* l, vertex* r) {
	if (!l || !r)
		t = l ? l : r;
	else if (l->prior > r->prior)
		merge(l->r, l->r, r),  t = l;
	else
		merge(r->l, l, r->l),  t = r;
}

void erase (vertex* &t, int key) {
	if (t->key == key)
		merge(t, t->l, t->r);
	else
		erase(key < t->key ? t->l : t->r, key);
}

vertex* unite(vertex* l, vertex* r) {
	if (!l || !r)  return l ? l : r;
	if (l->prior < r->prior)  swap (l, r);
	vertex* lt, rt;
	split(r, l->key, lt, rt);
	l->l = unite (l->l, lt);
	l->r = unite (l->r, rt);
	return l;
}
