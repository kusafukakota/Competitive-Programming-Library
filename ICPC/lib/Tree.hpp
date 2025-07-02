#pragma once

struct Tree : vector<vector<ll>> {
  using vector<vector<ll>>::operator=;

 private:
  void dfs_sz(int v, int p) {
    sz[v] = 1;
    ord.emplace_back(v);
    for(int i = p, x = 0; i != -1;) {
      bl[v][x] = i;
      i = bl[i][x], x++;
    }
    for(auto &nv : (*this)[v]) {
      if(nv == p) {
        if((int)(*this)[v].size() >= 2 && nv == (*this)[v][0]) { std::swap((*this)[v][0], (*this)[v][1]); }
        else { continue; }
      }
      dp[nv] = dp[v] + 1;
      dfs_sz(nv, v);
      sz[v] += sz[nv];
      if(sz[nv] > sz[(*this)[v][0]]) { std::swap(nv, (*this)[v][0]); }
    }
  }
  void dfs_hld(int v) {
    down[v] = id++;
    for(auto &nv : (*this)[v]) {
      if(nv == parent(v)) { continue; }
      nx[nv] = (nv == (*this)[v][0] ? nx[v] : nv);
      dfs_hld(nv);
    }
    up[v] = id;
  }
  vector<pair<int, int>> ascend(int u, int v) const {
    vector<pair<int, int>> r;
    while(nx[u] != nx[v]) {
      r.emplace_back(down[u], down[nx[u]]);
      u = parent(nx[u]);
    }
    if(u != v) { r.emplace_back(down[u], down[v] + 1); }
    return r;
  }
  vector<pair<int, int>> descend(int u, int v) const {
    if(u == v) { return {}; }
    if(nx[u] == nx[v]) { return {{down[u] + 1, down[v]}}; }
    auto r = descend(u, parent(nx[v]));
    r.emplace_back(down[nx[v]], down[v]);
    return r;
  }

 public:
  int n, root, id = 0;
  vector<array<int, 24>> bl;
  vector<int> dp, sz, ord, down, up, nx;
  Tree(int n_, int r = 0): n(n_), root(r) { this->resize(n); }
  Tree(const vector<vector<ll>> &g, int r = 0): n(g.size()), root(r) {
    *this = g;
    build();
  }
  void add_edge(int u, int v) {
    (*this)[u].emplace_back(v);
    (*this)[v].emplace_back(u);
  }
  void build() {
    bl.resize(n);
    dp.resize(n);
    sz.resize(n);
    down.assign(n, -1);
    up.assign(n, -1);
    nx.assign(n, root);
    for(auto &v : bl) { ranges::fill(v, -1); }
    dfs_sz(root, -1);
    dfs_hld(root);
  }
  int size() const { return n; }
  int depth(int i) const { return dp[i]; }
  int parent(int i) const { return i == root ? root : bl[i][0]; }
  int order(int i) const { return ord[i]; }
  int in(int i) const { return down[i]; }
  int out(int i) const { return up[i]; }
  int size(int i) const { return sz[i]; }
  int kth_ancestor(int i, int k) const {
    if(dp[i] < k) { return -1; }
    while(k) {
      int t = __builtin_ctz(k);
      i = bl[i][t], k ^= 1 << t;
    }
    return i;
  }
  int distance(int u, int v) { return dp[u] + dp[v] - dp[lca(u, v)] * 2; }
  bool onpath(int u, int x, int v) { return distance(u, v) == distance(u, x) + distance(x, v); }
  // vertex adjacent to u on u-v path
  int nxt(int u, int v) const {
    if(dp[u] >= dp[v]) { return parent(u); }
    int x = kth_ancestor(v, dp[v] - dp[u] - 1);
    return bl[x][0] == u ? x : bl[u][0];
  }
  vector<int> path(int u, int v) const {
    vector<int> pre, suf;
    while(dp[u] > dp[v]) {
      pre.emplace_back(u);
      u = bl[u][0];
    }
    while(dp[u] < dp[v]) {
      suf.emplace_back(v);
      v = bl[v][0];
    }
    while(u != v) {
      pre.emplace_back(u);
      suf.emplace_back(v);
      u = bl[u][0];
      v = bl[v][0];
    }
    pre.emplace_back(u);
    ranges::reverse(suf);
    copy(suf.begin(), suf.end(), back_inserter(pre));
    return pre;
  }
  int lca(int u, int v) {
    while(nx[u] != nx[v]) {
      if(down[u] < down[v]) { std::swap(u, v); }
      u = parent(nx[u]);
    }
    return dp[u] < dp[v] ? u : v;
  }
  // vertex at distance x from u on u-v path
  int jump(int u, int v, int x) {
    int lc = lca(u, v), d1 = dp[u] - dp[lc];
    if(x <= d1) { return kth_ancestor(u, x); }
    int d = d1 + dp[v] - dp[lc];
    if(x <= d) { return kth_ancestor(v, d - x); }
    return -1;
  }
  vector<int> diameter() {
    int s = ranges::max_element(dp) - dp.begin();
    vector<int> d(n, -1);
    d[s] = 0;
    queue<int> q;
    q.emplace(s);
    while(!q.empty()) {
      int v = q.front();
      q.pop();
      for(auto &nv : (*this)[v]) {
        if(d[nv] == -1) {
          d[nv] = d[v] + 1;
          q.emplace(nv);
        }
      }
    }
    int t = ranges::max_element(d) - d.begin();
    return path(t, s);
  }
  template<typename F> void query(int u, int v, bool vertex, const F &f) {
    int l = lca(u, v);
    for(auto &&[a, b] : ascend(u, l)) {
      int s = a + 1, t = b;
      s > t ? f(t, s) : f(s, t);
    }
    if(vertex) f(down[l], down[l] + 1);
    for(auto &&[a, b] : descend(l, v)) {
      int s = a, t = b + 1;
      s > t ? f(t, s) : f(s, t);
    }
  }
  template<typename F> void noncommutative_query(int u, int v, bool vertex, const F &f) {
    int l = lca(u, v);
    for(auto &&[a, b] : ascend(u, l)) { f(a + 1, b); }
    if(vertex) { f(down[l], down[l] + 1); }
    for(auto &&[a, b] : descend(l, v)) { f(a, b + 1); }
  }
  template<typename F> void subtree_query(int u, bool vertex, const F &f) {
    f(down[u] + int(!vertex), up[u]);
  }
};