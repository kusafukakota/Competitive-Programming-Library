#include <bits/stdc++.h>
using namespace std;
using ll = long long;

template<typename T> struct Weighted_Unionfind {
  vector<ll> par, rank;
  vector<T> diff_;
  Weighted_Unionfind(ll n): par(n), rank(n), diff_(n) {
    for(ll i = 0; i < n; i++) { par[i] = i, rank[i] = diff_[i] = 0; }
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
  ll operator[](ll i) { return root(i); }
  void operator()(ll x, ll y, T w) { unite(x, y, w); }
  void operator()(pair<ll, ll> x, T w) { unite(x, w); }
};

int main() {
  ios::sync_with_stdio(false);
  cin.tie(0);
  ll n, q;
  cin >> n >> q;
  Weighted_Unionfind<ll> u(n);
  vector<ll> v;
  for(ll i = 0; i < q; i++) {
    ll a, b, w;
    cin >> a >> b >> w;
    a--, b--;
    if(u.same(a, b)) {
      if(u.diff(a, b) == w) { v.emplace_back(i + 1); }
    }
    else {
      v.emplace_back(i + 1);
      u.unite(a, b, w);
    }
  }
  for(auto &i : v) { cout << i << " "; }
}
