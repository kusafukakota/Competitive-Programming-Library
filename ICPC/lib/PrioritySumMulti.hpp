#pragma once

#include <atcoder/segtree>
using namespace atcoder;

namespace PS {
using T = pair<ll, ll>;
T op(T l, T r) { return {l.first + r.first, l.second + r.second}; }
T e() { return {0, 0}; }
ll tar;
bool F(T x) { return tar > x.second; }
}  // namespace PS

struct PrioritySum {
 private:
  int n;
  segtree<PS::T, PS::op, PS::e> seg;
  vector<ll> s;

 public:
  PrioritySum() {}
  // insert クエリで追加される整数を予め追加 O(1)
  void use(ll x) { s.emplace_back(x); }
  // 構築 O(N log N)
  void build() {
    ranges::sort(s);
    s.erase(unique(s.begin(), s.end()), s.end());
    n = s.size();
    seg = segtree<PS::T, PS::op, PS::e>(n);
  }
  // x を c 個追加 O(log N)
  void insert(ll x, ll c = 1) {
    int idx = ranges::lower_bound(s, x) - s.begin();
    auto [sum, cnt] = seg.get(idx);
    seg.set(idx, {sum + x * c, cnt + c});
  }
  // x を c 個削除. 存在する数より多く消そうとすると壊れる O(log N)
  void erase(ll x, ll c = 1) { insert(x, -c); }
  // 昇順 k 個の和 O(log N)
  ll min(int k) const {
    if(k <= 0) { return 0; }
    PS::tar = k;
    int idx = seg.max_right<PS::F>(0);
    auto [sum, cnt] = seg.prod(0, idx);
    if(idx < n) { sum += s[idx] * (k - cnt); }
    return sum;
  }
  // 降順 k 個の和 O(log N)
  ll max(int k) const {
    if(k <= 0) { return 0; }
    PS::tar = k;
    int idx = seg.min_left<PS::F>(n) - 1;
    auto [sum, cnt] = seg.prod(idx, n);
    if(idx >= 0) { sum -= s[idx] * (cnt - k); }
    return sum;
  }
};