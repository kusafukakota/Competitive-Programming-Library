#pragma once

struct Interval {
 private:
  set<pair<ll, ll>> s;
  ll cnt, inf = 8e18;

 public:
  Interval(): cnt(0) {
    s.emplace(-inf, -inf);
    s.emplace(inf, inf);
  }
  // [l, r] が全て含まれているかを返す O(log N)
  bool contains(ll l, ll r) const {
    assert(l <= r);
    auto [L, R] = *prev(s.lower_bound({l + 1, l + 1}));
    return L <= l && r <= R;
  }
  // x が含まれているかを返す O(log N)
  bool contains(ll x) const { return contains(x, x); }
  // [l, r] が全て含まれている区間を返す．なければ{-inf, -inf}を返す O(log N)
  pair<ll, ll> covered_by(ll l, ll r) const {
    assert(l <= r);
    auto [L, R] = *prev(s.lower_bound({l + 1, l + 1}));
    if(L <= l && r <= R) { return {L, R}; }
    return {-inf, -inf};
  }
  // x が含まれている区間を返す．なければ{-inf, -inf}を返す O(log N)
  pair<ll, ll> covered_by(ll x) const { return covered_by(x, x); }
  // [l, r] を追加し，新たに追加された整数の個数を返す O(log N)
  ll insert(ll l, ll r) {
    assert(l <= r);
    auto it = prev(s.lower_bound({l + 1, l + 1}));
    if(it->first <= l && r <= it->second) { return 0; }
    ll sum_erased = 0;
    if(it->first <= l && l <= it->second + 1) {
      l = it->first;
      sum_erased += it->second - it->first + 1;
      it = s.erase(it);
    }
    else it = next(it);
    while(r > it->second) {
      sum_erased += it->second - it->first + 1;
      it = s.erase(it);
    }
    if(it->first - 1 <= r && r <= it->second) {
      sum_erased += it->second - it->first + 1;
      r = it->second;
      s.erase(it);
    }
    s.emplace(l, r);
    cnt += r - l + 1 - sum_erased;
    return r - l + 1 - sum_erased;
  }
  // x を追加し，新たに追加された整数の個数を返す(0 or 1) O(log N)
  ll insert(ll x) {
    auto nit = s.lower_bound({x + 1, x + 1}), it = prev(nit);
    auto [l, r] = *it;
    auto [nl, nr] = *nit;
    if(l <= x && x <= r) { return 0; }
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
    cnt++;
    return 1;
  }
  // [l, r] を削除し，削除された整数の個数を返す O(log N)
  ll erase(ll l, ll r) {
    assert(l <= r);
    auto it = prev(s.lower_bound({l + 1, l + 1}));
    if(it->first <= l && r <= it->second) {
      if(it->first < l) { s.emplace(it->first, l - 1); }
      if(r < it->second) { s.emplace(r + 1, it->second); }
      s.erase(it);
      cnt -= r - l + 1;
      return r - l + 1;
    }
    ll ret = 0;
    if(it->first <= l && l <= it->second) {
      ret += it->second - l + 1;
      if(it->first < l) { s.emplace(it->first, l - 1); }
      it = s.erase(it);
    }
    else it = next(it);
    while(it->second <= r) {
      ret += it->second - it->first + 1;
      it = s.erase(it);
    }
    if(it->first <= r && r <= it->second) {
      ret += r - it->first + 1;
      if(r < it->second) { s.emplace(r + 1, it->second); }
      s.erase(it);
    }
    cnt -= ret;
    return ret;
  }
  // x を削除し，削除された整数の個数を返す(0 or 1) O(log N)
  ll erase(ll x) {
    auto it = prev(s.lower_bound({x + 1, x + 1}));
    auto [l, r] = *it;
    if(!(l <= x && x <= r)) { return 0; }
    s.erase(it);
    if(l != x) { s.emplace(l, x - 1); }
    if(r != x) { s.emplace(x + 1, r); }
    cnt--;
    return 1;
  }
  // 区間の個数を返す O(1)
  int size() const { return (int)s.size() - 2; }
  // いずれかの区間に含まれている整数の個数を返す O(1)
  ll count() const { return cnt; }
  // どの区間にも含まれていない x 以上の最小の整数を返す O(log N)
  ll mex(ll x = 0) const {
    auto [l, r] = *prev(s.lower_bound({x + 1, x + 1}));
    return l <= x && x <= r ? r + 1 : x;
  }
  // x と y が同じ区間に含まれているかを返す O(log N)
  bool same(ll x, ll y) const {
    auto ix = covered_by(x).first, iy = covered_by(y).first;
    return ix == iy && ix != -inf;
  }
  void clear() {
    s.clear();
    s.emplace(-inf, -inf);
    s.emplace(inf, inf);
    cnt = 0;
  }
  // 出力(for debug)
  void dump() const {
    for(auto &[l, r] : s) {
      if(l == -inf || r == inf) { continue; }
      cout << "[" << l << ", " << r << "] ";
    }
    cout << "\n";
  }
} I;
