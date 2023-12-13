struct Rollback_Unionfind {
  vector<ll> par;
  stack<pair<ll, ll>> history;
  Rollback_Unionfind(ll n): par(n, -1) {}
  ll root(ll x) {
    if(par[x] < 0) { return x; }
    else { return root(par[x]); }
  }
  void unite(ll x, ll y) {
    x = root(x), y = root(y);
    history.emplace(x, par[x]);
    history.emplace(y, par[y]);
    if(x == y) { return; }
    if(par[x] > par[y]) { swap(x, y); }
    par[x] += par[y];
    par[y] = x;
  }
  void unite(pair<ll, ll> x) { unite(x.first, x.second); }
  bool same(ll x, ll y) { return root(x) == root(y); }
  bool same(pair<ll, ll> x) { return same(x.first, x.second); }
  ll size(ll x) { return -par[root(x)]; }
  void undo() {
    for(ll i = 0; i < 2; i++) {
      par[history.top().first] = history.top().second;
      history.pop();
    }
  }
  void snapshot() {
    while(!history.empty()) { history.pop(); }
  }
  void rollback() {
    while(!history.empty()) { undo(); }
  }
  ll operator[](ll i) { return root(i); }
  void operator()(ll x, ll y) { unite(x, y); }
  void operator()(pair<ll, ll> x) { unite(x); }
};
