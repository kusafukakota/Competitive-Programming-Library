struct Tree : vector<vector<ll>> {
 private:
  void dfs_sz(ll v, ll p) {
    sz[v] = 1;
    ord.emplace_back(v);
    for(ll i = p, x = 0; i != -1;) {
      bl[v][x] = i;
      i = bl[i][x], x++;
    }
    for(auto &nv : (*this)[v]) {
      if(nv == p) {
        if((ll)(*this)[v].size() >= 2 && nv == (*this)[v][0]) { std::swap((*this)[v][0], (*this)[v][1]); }
        else { continue; }
      }
      dp[nv] = dp[v] + 1;
      dfs_sz(nv, v);
      sz[v] += sz[nv];
      if(sz[nv] > sz[(*this)[v][0]]) { std::swap(nv, (*this)[v][0]); }
    }
  }
  void dfs_hld(ll v) {
    down[v] = id++;
    for(auto &nv : (*this)[v]) {
      if(nv == par(v)) { continue; }
      nx[nv] = (nv == (*this)[v][0] ? nx[v] : nv);
      dfs_hld(nv);
    }
    up[v] = id;
  }
  vector<pair<ll, ll>> ascend(ll u, ll v) const {
    vector<pair<ll, ll>> r;
    while(nx[u] != nx[v]) {
      r.emplace_back(down[u], down[nx[u]]);
      u = par(nx[u]);
    }
    if(u != v) { r.emplace_back(down[u], down[v] + 1); }
    return r;
  }
  vector<pair<ll, ll>> descend(ll u, ll v) const {
    if(u == v) { return {}; }
    if(nx[u] == nx[v]) { return {{down[u] + 1, down[v]}}; }
    auto r = descend(u, par(nx[v]));
    r.emplace_back(down[nx[v]], down[v]);
    return r;
  }

 public:
  ll n, root, id = 0;
  vector<array<ll, 24>> bl;
  vector<ll> dp, sz, ord, down, up, nx;
  Tree(ll n_, ll r = 0): n(n_), root(r) { this->resize(n); }
  Tree(vector<vector<ll>> &g, ll r = 0): n(g.size()), root(r) {
    *this = g;
    build();
  }
  void add_edge(ll u, ll v) {
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
  ll depth(ll i) const { return dp[i]; }
  ll par(ll i) const { return i == root ? root : bl[i][0]; }
  ll order(ll i) const { return ord[i]; }
  ll in(ll i) const { return down[i]; }
  ll out(ll i) const { return up[i]; }
  ll size(ll i) const { return sz[i]; }
  ll kth_ancestor(ll i, ll k) const {
    if(dp[i] < k) { return -1; }
    while(k) {
      ll t = __builtin_ctz(k);
      i = bl[i][t], k ^= 1 << t;
    }
    return i;
  }
  ll dis(ll u, ll v) { return dp[u] + dp[v] - dp[lca(u, v)] * 2; }
  bool onpath(ll u, ll v, ll x) { return dis(u, v) == dis(u, x) + dis(x, v); }
  ll nxt(ll u, ll v) const {
    if(dp[u] >= dp[v]) { return par(u); }
    ll x = kth_ancestor(v, dp[v] - dp[u] - 1);
    return bl[x][0] == u ? x : bl[u][0];
  }
  vector<ll> path(ll u, ll v) const {
    vector<ll> pre, suf;
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
  ll lca(ll u, ll v) {
    while(nx[u] != nx[v]) {
      if(down[u] < down[v]) { std::swap(u, v); }
      u = par(nx[u]);
    }
    return dp[u] < dp[v] ? u : v;
  }
  ll jump(ll u, ll v, ll x) {
    ll lc = lca(u, v), d1 = dp[u] - dp[lc];
    if(x <= d1) { return kth_ancestor(u, x); }
    ll d = d1 + dp[v] - dp[lc];
    if(x <= d) { return kth_ancestor(v, d - x); }
    return -1;
  }
  vector<ll> diameter() {
    ll s = ranges::max_element(dp) - dp.begin();
    vector<ll> d(n, -1);
    d[s] = 0;
    queue<ll> q;
    q.emplace(s);
    while(!q.empty()) {
      ll v = q.front();
      q.pop();
      for(auto &nv : (*this)[v]) {
        if(d[nv] == -1) {
          d[nv] = d[v] + 1;
          q.emplace(nv);
        }
      }
    }
    ll t = ranges::max_element(d) - d.begin();
    return path(t, s);
  }
  template<typename F> void query(ll u, ll v, bool vertex, const F &f) {
    ll l = lca(u, v);
    for(auto &&[a, b] : ascend(u, l)) {
      ll s = a + 1, t = b;
      s > t ? f(t, s) : f(s, t);
    }
    if(vertex) f(down[l], down[l] + 1);
    for(auto &&[a, b] : descend(l, v)) {
      ll s = a, t = b + 1;
      s > t ? f(t, s) : f(s, t);
    }
  }
  template<typename F> void noncommutative_query(ll u, ll v, bool vertex, const F &f) {
    ll l = lca(u, v);
    for(auto &&[a, b] : ascend(u, l)) { f(a + 1, b); }
    if(vertex) { f(down[l], down[l] + 1); }
    for(auto &&[a, b] : descend(l, v)) { f(a, b + 1); }
  }
  template<typename F> void subtree_query(ll u, bool vertex, const F &f) {
    f(down[u] + int(!vertex), up[u]);
  }
};
