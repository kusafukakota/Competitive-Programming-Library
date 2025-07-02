#pragma once

template<typename T> struct WeightedUnionfind {
  vector<ll> par, rank;
  vector<T> diff_;
  WeightedUnionfind(ll n): par(n), rank(n), diff_(n) {
    for(ll i = 0; i < n; i++) { par[i] = i, rank[i] = 0, diff_[i] = 0; }
  }
  ll root(ll x) {
    if(par[x] == x) { return x; }
    else {
      ll r = root(par[x]);
      diff_[x] += diff_[par[x]];
      return par[x] = r;
    }
  }
  T weight(ll x) {
    root(x);
    return diff_[x];
  }
  // y - x = w
  void unite(ll x, ll y, T w) {
    w += weight(x) - weight(y);
    x = root(x), y = root(y);
    if(x == y) { return; }
    if(rank[x] < rank[y]) { swap(x, y), w = -w; }
    if(rank[x] == rank[y]) { rank[x]++; }
    par[y] = x;
    diff_[y] = w;
  }
  void unite(pair<ll, ll> x, T w) { unite(x.first, x.second, w); }
  bool same(ll x, ll y) { return root(x) == root(y); }
  bool same(pair<ll, ll> x) { return same(x.first, x.second); }
  T diff(ll x, ll y) { return weight(y) - weight(x); }
};