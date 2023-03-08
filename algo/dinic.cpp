struct edge {
  int v, u, c, flow;
};

const int N = 110;
const int INF = 1e9;

vector<edge> edgeList;
vector<int> edgeInd[N];
int dis[N], ptr[N];

void addEdge(int v, int u, int c) {
  edgeInd[v].push_back((int)edgeList.size());
  edgeList.push_back({v, u, c, 0});
  edgeInd[u].push_back((int)edgeList.size());
  edgeList.push_back({u, v, c, 0}); // e.c can be 0 - oriented
}

int bfsDinic(int s, int t) {
  queue<int> q;
  q.push(s);
  dis[s] = 0;
  while (!q.empty()) {
    int v = q.front();
    q.pop();
    if (v == t)
      break;
    for (int id : edgeInd[v]) {
      auto e = edgeList[id];
      if (dis[e.u] == -1 && e.c - e.flow > 0) {
        q.push(e.u);
        dis[e.u] = dis[v] + 1;
      }
    }
  }
  return dis[t] != -1;
}

int dfsDinic(int v, int t, int flow) {
  if (!flow)
    return 0;
  if (v == t)
    return flow;
  for ( ; ptr[v] < (int)edgeInd[v].size(); ptr[v]++) {
    int id = edgeInd[v][ptr[v]];
    auto e = edgeList[id];
    if (dis[e.u] != dis[v] + 1)
      continue;
    int pushed = dfsDinic(e.u, t, min(flow, e.c - e.flow));
    if (pushed) {
      edgeList[id].flow += pushed;
      edgeList[id ^ 1].flow -= pushed;
      return pushed;
    }
  }
  return 0;
}

int dinic(int s, int t, int n) {
  int flow = 0;
  while (true) {
    fill(dis + 1, dis + 1 + n, -1); // INDEXING FROM 1
    if (!bfsDinic(s, t))
      break;
    fill(ptr + 1, ptr + 1 + n, 0);
    while (true) {
      int pushed = dfsDinic(s, t, INF);
      if (!pushed)
        break;
      flow += pushed;
    }
  }
  return flow;
}
