#pragma once

template<typename T> struct SparseTable {
  inline static constexpr T INF = numeric_limits<T>::max() / 2;
  int N;
  vector<vector<T>> table;
  T f(T a, T b) { return min(a, b); }
  SparseTable() {}
  SparseTable(const vector<T> &v): N(ssize(v)) {
    int b = 1;
    while((1 << b) <= N) { ++b; }
    table.emplace_back(v);
    for(int i = 1; i < b; i++) {
      table.emplace_back(vector<T>(N, INF));
      for(int j = 0; j + (1 << i) <= N; j++) {
        table[i][j] = f(table[i - 1][j], table[i - 1][j + (1 << (i - 1))]);
      }
    }
  }
  T query(int l, int r) {  // [l, r)
    assert(0 <= l && l <= r && r <= N);
    if(l == r) { return INF; }
    int b = 31 - __builtin_clz(r - l);
    return f(table[b][l], table[b][r - (1 << b)]);
  }
};

#include <atcoder/string>
using namespace atcoder;

template<typename T> struct StringSearch {
  const T &S;
  ll N;
  vector<int> sa, la, inv;
  SparseTable<int> sparse;
  StringSearch(const T &s_): S(s_), N(ssize(S)) {
    sa = suffix_array(S);
    la = lcp_array(S, sa);
    inv.resize(N);
    for(ll i = 0; i < N; i++) { inv[sa[i]] = i; }
    sparse = SparseTable<int>{la};
  }
  // lcp(s[i, N), s[j, N))
  ll lcp(ll i, ll j) {
    assert(0 <= min(i, j) && max(i, j) < N);
    if(i == j) { return N - i; }
    auto [x, y] = minmax(inv[i], inv[j]);
    return sparse.query(x, y);
  }
  // lcp(s[a, b), s[c, d))
  ll lcp(ll a, ll b, ll c, ll d) {
    assert(0 <= a && a <= b && b <= N);
    assert(0 <= c && c <= d && d <= N);
    ll l = lcp(a, c);
    return min({l, b - a, d - c});
  }
  ll lcp(pair<ll, ll> p, pair<ll, ll> q) {
    return lcp(p.first, p.second, q.first, q.second);
  }
  // s[i, N) > s[j, N) : 1
  // s[i, N) = s[j, N) : 0
  // s[i, N) < s[j, N) : -1
  ll compare(ll i, ll j) {
    assert(0 <= min(i, j) && max(i, j) < N);
    if(i == j) { return 0; }
    return inv[i] < inv[j] ? -1 : 1;
  }
  // s[a, b) > s[c, d) : 1
  // s[a, b) = s[c, d) : 0
  // s[a, b) < s[c, d) : -1
  ll compare(ll a, ll b, ll c, ll d) {
    ll l = lcp(a, b, c, d);
    return a + l == b     ? (c + l == d ? 0 : -1)
    : c + l == d          ? 1
    : S[a + l] < S[c + l] ? -1
                          : 1;
  }
  ll compare(pair<ll, ll> p, pair<ll, ll> q) {
    return compare(p.first, p.second, q.first, q.second);
  }
};