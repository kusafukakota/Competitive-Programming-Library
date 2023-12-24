using S = pair<ll, ll>;
S op(S l, S r) { return {l.first + r.first, l.second + r.second}; }
S e() { return {0, 0}; }
ll tar;
bool F(S x) { return tar > x.second; }

struct PrioritySum {
  ll n;
  segtree<S, op, e> seg;
  set<ll> s;
  map<ll, ll> comp;
  vector<ll> inv;
  bool built;
  PrioritySum() : built(false){}
  void use(ll x) {
    assert(!built);
    s.insert(x);
  }
  void build() {
    assert(!built);
    built = true;
    n = ssize(s);
    seg = segtree<S, op, e>(n);
    ll idx = 0;
    for(auto &i : s) {
      comp[i] = idx;
      inv.emplace_back(i);
      idx++;
    }
  }
  void insert(ll x, ll c = 1) {
    assert(built);
    auto it = comp.find(x);
    assert(it != comp.end());
    ll idx = it->second;
    auto [sum, cnt] = seg.get(idx);
    seg.set(idx, {sum + x * c, cnt + c});
  }
  void erase(ll x, ll c = 1) { insert(x, -c); }
  ll min(ll k) {
    assert(built);
    tar = k;
    ll idx = seg.max_right<F>(0);
    assert(idx <= n);
    auto [sum, cnt] = seg.prod(0, idx);
    sum += inv[idx] * (k - cnt);
    return sum;
  }
  ll max(ll k) {
    assert(built);
    tar = k;
    ll idx = seg.min_left<F>(n) - 1;
    assert(idx >= 0);
    auto [sum, cnt] = seg.prod(idx, n);
    sum -= inv[idx] * (cnt - k);
    return sum;
  }
};
