template<typename S, auto op, auto e> struct RollbackUnionfind {
  vector<int> par;
  vector<S> val;
  stack<tuple<int, int, S, int>> history;
  int snap, cnt;
  RollbackUnionfind() = default;
  RollbackUnionfind(int n): RollbackUnionfind(vector<S>(n, e())) {}
  RollbackUnionfind(const vector<S> &v): par(v.size(), -1), val(v), snap(0), cnt(v.size()) {}
  int root(int x) const {
    if(par[x] < 0) { return x; }
    return root(par[x]);
  }
  void unite(int x, int y) {
    x = root(x), y = root(y);
    history.emplace(-1, 0, e(), cnt);
    history.emplace(x, par[x], val[x], cnt);
    history.emplace(y, par[y], val[y], cnt);
    if(x == y) { return; }
    if(par[x] > par[y]) { swap(x, y); }
    par[x] += par[y];
    par[y] = x;
    val[x] = op(val[x], val[y]);
    cnt--;
  }
  void undo() {
    assert(!history.empty());
    while(true) {
      auto [x, p, v, c] = history.top();
      history.pop();
      if(x == -1) { break; }
      par[x] = p;
      val[x] = v;
      cnt = c;
    }
  }
  bool same(int x, int y) const { return root(x) == root(y); }
  int size(int x) const { return -par[root(x)]; }
  int count() const { return cnt; }
  S prod(int x) const { return val[root(x)]; }
  void update(int x, const S &v) {
    x = root(x);
    history.emplace(-1, 0, e(), cnt);
    history.emplace(x, par[x], val[x], cnt);
    val[x] = op(val[x], v);
  }
  int state() const { return history.size(); }
  void snapshot() { snap = history.size(); }
  void rollback(int p = -1) {
    if(p == -1) { p = snap; }
    while(p < (int)history.size()) { undo(); }
  }
};
