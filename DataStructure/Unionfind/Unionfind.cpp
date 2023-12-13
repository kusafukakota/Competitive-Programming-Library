struct Unionfind {
  vector<ll> par;
  ll e = 0, v;
  Unionfind(ll n): par(n, -1), v(n) {}
  Unionfind(vector<vector<ll>> g): par(g.size(), -1), v(g.size()) {
    for(ll i = 0; i < v; i++) {
      for(auto &j : g[i]) {
        if(i < j) { unite(i, j); }
      }
    }
  }
  ll root(ll x) {
    if(par[x] < 0) { return x; }
    return par[x] = root(par[x]);
  }
  void unite(ll x, ll y) {
    x = root(x), y = root(y);
    if(x == y) { return; }
    if(par[x] > par[y]) { swap(x, y); }
    par[x] += par[y];
    par[y] = x;
    e++;
  }
  void unite(pair<ll, ll> x) { unite(x.first, x.second); }
  bool same(ll x, ll y) { return root(x) == root(y); }
  bool same(pair<ll, ll> x) { return same(x.first, x.second); }
  ll size(ll x) { return -par[root(x)]; }
  vector<vector<ll>> group() {
    vector<vector<ll>> r(v);
    for(ll i = 0; i < v; i++) { r[root(i)].emplace_back(i); }
    r.erase(remove_if(begin(r), end(r), [&](vector<ll> &r_) { return r_.empty(); }));
    return r;
  }
  ll operator[](ll i) { return root(i); }
  void operator()(ll x, ll y) { unite(x, y); }
  void operator()(pair<ll, ll> x) { unite(x); }
  ll operator()() { return v - e; }
};
