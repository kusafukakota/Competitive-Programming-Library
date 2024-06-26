struct MEX {
  set<pair<ll, ll>> s;
  MEX() {
    s.emplace(-1e18, -1e18);
    s.emplace(1e18, 1e18);
  }
  bool contains(ll x) const {
    auto it = prev(s.lower_bound({x + 1, x + 1}));
    auto [l, r] = *it;
    return l <= x && x <= r;
  }
  bool insert(ll x) {
    auto nit = s.lower_bound({x + 1, x + 1}), it = prev(nit);
    auto [l, r] = *it;
    auto [nl, nr] = *nit;
    if(l <= x && x <= r) { return false; }
    if(r == x - 1) {
      if(nl == x + 1) {
        s.erase(it);
        s.erase(nit);
        s.emplace(l, nr);
      }
      else {
        s.erase(it);
        s.emplace(l, x);
      }
    }
    else {
      if(nl == x + 1) {
        s.erase(nit);
        s.emplace(x, nr);
      }
      else { s.emplace(x, x); }
    }
    return true;
  }
  void erase(ll x) {
    auto it = prev(s.lower_bound({x + 1, x + 1}));
    auto [l, r] = *it;
    s.erase(it);
    if(l != x) { s.emplace(l, x - 1); }
    if(r != x) { s.emplace(x + 1, r); }
  }
  ll query(ll x = 0) const {
    auto [l, r] = *prev(s.lower_bound({x + 1, x + 1}));
    return l <= x && x <= r ? r + 1 : x;
  }
};
