using T = pair<ll, ll>;
T op(T l, T r) { return {l.first + r.first, l.second + r.second}; }
T e() { return {0, 0}; }
ll tar;
bool F(T x) { return tar > x.second; }

struct PrioritySum {
  int n;
  segtree<T, op, e> seg;
  vector<ll> s;
  PrioritySum() {}
  void use(ll x) { s.emplace_back(x); }
  void build() {
    ranges::sort(s);
    s.erase(unique(s.begin(), s.end()), s.end());
    n = s.size();
    seg = segtree<T, op, e>(n);
  }
  void insert(ll x, ll c = 1) {
    int idx = ranges::lower_bound(s, x) - s.begin();
    auto [sum, cnt] = seg.get(idx);
    seg.set(idx, {sum + x * c, cnt + c});
  }
  void erase(ll x, ll c = 1) { insert(x, -c); }
  ll min(int k) const {
    if(!k) { return 0; }
    tar = k;
    int idx = seg.max_right<F>(0);
    auto [sum, cnt] = seg.prod(0, idx);
    sum += s[idx] * (k - cnt);
    return sum;
  }
  ll max(int k) const {
    if(!k) { return 0; }
    tar = k;
    int idx = seg.min_left<F>(n) - 1;
    auto [sum, cnt] = seg.prod(idx, n);
    sum -= s[idx] * (cnt - k);
    return sum;
  }
};
