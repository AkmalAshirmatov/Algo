struct edge {
  int v, u;
  ll c, flow, cost;
};

vector<edge> edgeList;
vector<int> edgeInd[N];

void addEdge(int v, int u, ll c, ll cost) {
  edgeInd[v].push_back((int)edgeList.size());
  edgeList.push_back({v, u, c, 0, cost});
  edgeInd[u].push_back((int)edgeList.size());
  edgeList.push_back({u, v, 0, 0, -cost});
}

void solve(){
	for (int i = 1; i <= n; i++){
		for (ll x : kol[i]){
			ll res = a[i] * x * x + b[i] * x + c[i];
			addEdge(i, mp[x], 1, res);
			st.insert(mp[x]);
		}
	}
	int s = 0, t = cnt++;
  for (int i = 1; i <= n; i++) {
    addEdge(s, i, 1, 0);
  }
  for (auto i : st){
    addEdge(i, t, 1, 0);
  }
  int numvertex = cnt;
  ll flow = 0, cost = 0;
  while (flow < needflow) {
    vector<ll> d(numvertex, INF);
    vector<int> from(numvertex, 0);
    d[s] = 0;
    set<pair<ll, int> > q;
    q.insert(make_pair(d[s], s));
    while (!q.empty()) {
      int v = q.begin()->second;
      q.erase(q.begin());
      for (int id : edgeInd[v]) {
        auto e = edgeList[id];
        if (e.flow < e.c && d[e.u] > d[v] + e.cost) {
          q.erase(make_pair(d[e.u], e.u));
          d[e.u] = d[v] + e.cost;
          from[e.u] = id;
          q.insert(make_pair(d[e.u], e.u));
        }
      }
    }
    ll curflow = needflow - flow;
    for (int v = t; v != s; ) {
      curflow = min(curflow, edgeList[from[v]].c - edgeList[from[v]].flow);
      v = edgeList[from[v]].v;
    }
    for (int v = t; v != s; ) {
      edgeList[from[v]].flow += curflow;
      edgeList[from[v] ^ 1].flow -= curflow;
      v = edgeList[from[v]].v;
    }
    cost += d[t] * curflow;
    flow += curflow;
  }
}

vector<int> id(numvertex, 0);
vector<ll> d(numvertex, INF);
vector<int> q(numvertex);
vector<int> from(numvertex);
int qh=0, qt=0;
q[qt++] = s;
d[s] = 0;
while (qh != qt) {
  int v = q[qh++];
  id[v] = 2;
  if (qh == numvertex) qh = 0;
  for (int eid : edgeInd[v]) {
    auto e = edgeList[eid];
    if (e.flow < e.c && d[e.u] > d[v] + e.cost) {
      d[e.u] = d[v] + e.cost;
      if (id[e.u] == 0) {
        q[qt++] = e.u;
        if (qt == numvertex) qt = 0;
      }
      else if (id[e.u] == 2) {
        if (--qh == -1) qh = numvertex-1;
        q[qh] = e.u;
      }
      id[e.u] = 1;
      from[e.u] = eid;
    }
  }
}
