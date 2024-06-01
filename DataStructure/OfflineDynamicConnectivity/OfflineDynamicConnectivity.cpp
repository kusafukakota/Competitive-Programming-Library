template<typename S, auto op, auto e> struct RollbackUnionfind {
 private:
  vector<int> par;
  vector<S> val;
  stack<tuple<int, int, S, int>> history;
  int snap, cnt;

 public:
  RollbackUnionfind() = default;
  RollbackUnionfind(int n): RollbackUnionfind(vector<S>(n, e())) {}
  RollbackUnionfind(const vector<S> &v): par(v.size(), -1), val(v), snap(0), cnt(v.size()) {}
  int root(int v) const {
    if(par[v] < 0) { return v; }
    return root(par[v]);
  }
  void unite(int u, int v) {
    u = root(u), v = root(v);
    history.emplace(-1, 0, e(), cnt);
    history.emplace(u, par[u], val[u], cnt);
    history.emplace(v, par[v], val[v], cnt);
    if(u == v) { return; }
    if(par[u] > par[v]) { swap(u, v); }
    par[u] += par[v];
    par[v] = u;
    val[u] = op(val[u], val[v]);
    cnt--;
  }
  void undo() {
    assert(!history.empty());
    while(true) {
      auto [v, p, x, c] = history.top();
      history.pop();
      if(v == -1) { break; }
      par[v] = p;
      val[v] = x;
      cnt = c;
    }
  }
  bool same(int u, int v) const { return root(u) == root(v); }
  int size(int v) const { return -par[root(v)]; }
  int count() const { return cnt; }
  S prod(int v) const { return val[root(v)]; }
  void update(int v, const S &x) {
    v = root(v);
    history.emplace(-1, 0, e(), cnt);
    history.emplace(v, par[v], val[v], cnt);
    val[v] = op(val[x], x);
  }
  int state() const { return history.size(); }
  void snapshot() { snap = history.size(); }
  void rollback(int p = -1) {
    if(p == -1) { p = snap; }
    while(p < (int)history.size()) { undo(); }
  }
};

template<typename S, auto op, auto e> struct OfflineDynamicConnectivity {
 private:
  int idx;
  multimap<pair<int, int>, int> open;
  vector<tuple<int, int, int, int>> closed;
  vector<tuple<int, int, S>> query_update;
  map<int, pair<int, int>> query_same;
  map<int, int> query_prod, query_size;
  vector<int> query_count;
  vector<S> val;

 public:
  OfflineDynamicConnectivity() = default;
  OfflineDynamicConnectivity(int n): OfflineDynamicConnectivity(vector<S>(n, e())) {}
  OfflineDynamicConnectivity(const vector<S> &v): val(v), idx(0) {}
  void unite(int u, int v) {
    auto edge = minmax(u, v);
    open.emplace(edge, ++idx);
  }
  void cut(int u, int v) {
    auto edge = minmax(u, v);
    auto it = open.find(edge);
    assert(it != open.end());
    closed.emplace_back(edge.first, edge.second, it->second, ++idx);
    open.erase(it);
  }
  void update(int v, const S &x) { query_update.emplace_back(++idx, v, x); }
  void same(int u, int v) { query_same[++idx] = {u, v}; }
  void prod(int v) { query_prod[++idx] = v; }
  void size(int v) { query_size[++idx] = v; }
  void count() { query_count.emplace_back(++idx); }
  vector<pair<int, S>> build() {
    idx++;
    for(auto &[edge, s] : open) { closed.emplace_back(edge.first, edge.second, s, idx); }
    int size = bit_ceil((unsigned)idx);
    vector<vector<pair<int, int>>> edges(size << 1);
    vector<vector<pair<int, S>>> updates(size << 1);
    for(auto &[u, v, s, t] : closed) {
      for(s += size, t += size; s < t; s >>= 1, t >>= 1) {
        if(s & 1) { edges[s++].emplace_back(u, v); }
        if(t & 1) { edges[--t].emplace_back(u, v); }
      }
    }
    for(auto &[s, v, x] : query_update) {
      int t = size;
      for(s += size, t += size; s < t; s >>= 1, t >>= 1) {
        if(s & 1) { updates[s++].emplace_back(v, x); }
        if(t & 1) { updates[--t].emplace_back(v, x); }
      }
    }
    RollbackUnionfind<S, op, e> uf(val);
    vector<pair<int, S>> r;
    auto dfs = [&](auto &&dfs, int k) -> void {
      for(auto &[u, v] : edges[k]) { uf.unite(u, v); }
      for(auto &[v, x] : updates[k]) { uf.update(v, x); }
      if(k < size) {
        dfs(dfs, 2 * k);
        dfs(dfs, 2 * k + 1);
      }
      else if(k < size + idx) {
        if(query_same.contains(k - size)) {
          auto [u, v] = query_same[k - size];
          r.emplace_back(uf.same(u, v), e());
        }
        if(query_prod.contains(k - size)) { r.emplace_back(false, uf.prod(query_prod[k - size])); }
        if(query_size.contains(k - size)) { r.emplace_back(uf.size(query_size[k - size]), e()); }
        if(ranges::binary_search(query_count, k - size)) { r.emplace_back(uf.count(), e()); }
      }
      for(int i = 0; i < (int)(edges[k].size() + updates[k].size()); i++) { uf.undo(); }
    };
    dfs(dfs, 1);
    return r;
  }
};
