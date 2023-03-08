int n, m;
vector<int> g[N];

void read() {
	cin >> n >> m;
	for (int i = 0; i < m; i++) {
		int u, v; cin >> u >> v; u--; v--;
		g[u].push_back(v); g[v].push_back(u);
	}
}
int tin[N], up[N], timer = 0, used[N];
vector<pair<int, int>> st;
vector<pair<int, int>> e[N];
int topQ = 0;

void dfsTin(int v, int p) {
	used[v] = true;
	tin[v] = up[v] = timer++;
	for (auto i : g[v]) {
		if (i == p) continue;
		if (used[i]) {
			chkmin(up[v], tin[i]);
		} else {
			dfsTin(i, v);
			chkmin(up[v], up[i]);
		}
	}
}
void dfsColor(int v, int p, int c) {
	used[v] = true;
	for (auto i : g[v]) {
		if (i == p) continue;
		if (!used[i]) {
			if (up[i] >= tin[v]) {
				int nc = topQ++;
				e[nc].push_back({i, v});
				dfsColor(i, v, nc);
			} else {
				e[c].push_back({i, v});
				dfsColor(i, v, c);
			}
		} else if (tin[i] < tin[v]) {
			e[c].push_back({i, v});
		}
	}
}
vector<int> comp[N];
void buildBlockCutTree() {
	fill(used, used + n, false);
	dfsTin(0, 0);
	fill(used, used + n, false);
	dfsColor(0, 0, -1);
	for (int i = 0; i < n; i++) {
		g[i].clear();
	}
	for (int i = 0; i < topQ; i++) {
		for (auto j : e[i]) {
			comp[i].push_back(j.first);
			comp[i].push_back(j.second);
		}
		sort(all(comp[i]));
		comp[i].resize(unique(all(comp[i])) - comp[i].begin());
		for (auto x : comp[i]) {
			g[x].push_back(n + i);
			g[n + i].push_back(x);
		}
	}
}
int h[N];
int dp[N];
void dfsDp(int v, int p) {
	dp[v] = 1;
	for (auto i : g[v]) {
		if (i == p) continue;
		h[i] = h[v] + 1;
		dfsDp(i, v);
		dp[v] = mul(dp[v], dp[i] + h[i] % 2);
	}
}
void calcDp() {
	dfsDp(0, 0);
}
int ans;
void makeAns() {
	ans = 1;
	for (int i = 0; i < N; i++) {
		if (h[i] & 1) continue;
		ans = add(ans, dp[i]);
	}
}
void run() {
	buildBlockCutTree();
	calcDp();
	makeAns();
}
