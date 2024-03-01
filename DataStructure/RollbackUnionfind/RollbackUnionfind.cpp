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
