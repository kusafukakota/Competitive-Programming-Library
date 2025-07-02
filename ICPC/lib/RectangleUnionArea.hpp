#pragma once

#include <atcoder/lazysegtree>
using namespace atcoder;

namespace RU {
using T = pair<ll, ll>;
using F = ll;
T op(T l, T r) {
  if(l.first != r.first) { return min(l, r); }
  return {l.first, l.second + r.second};
}
T e() { return {1e18, 0}; }
T fx(F f, T x) { return {x.first + f, x.second}; }
F fg(F f, F g) { return f + g; }
F id() { return 0; }
}  // namespace RU

struct RectangleUnionArea {
  vector<array<ll, 4>> v;
  RectangleUnionArea() {}
  RectangleUnionArea(ll N) { v.reserve(N); }
  void add(ll lx, ll rx, ll ly, ll ry) { v.push_back({lx, rx, ly, ry}); }
  ll build() {
    if(v.empty()) { return 0; }
    ll N = v.size();
    struct event {
      ll x, ly, ry;
      bool add;
    };
    vector<event> ev;
    vector<RU::T> y;
    for(int i = 0; i < N; i++) {
      auto [l, r, d, u] = v[i];
      y.emplace_back(d, i);
      y.emplace_back(u, i + N);
    }
    ranges::sort(y);
    vector<RU::T> dy;
    ll uniy = 0, py = y[0].first;
    for(int i = 0; i < 2 * N; i++) {
      if(y[i].first != py) {
        dy.emplace_back(0, y[i].first - py);
        py = y[i].first;
        uniy++;
      }
      if(y[i].second < N) { v[y[i].second][2] = uniy; }
      else { v[y[i].second - N][3] = uniy; }
    }
    for(auto &[l, r, d, u] : v) {
      ev.push_back(event{l, d, u, true});
      ev.push_back(event{r, d, u, false});
    }
    sort(ev.begin(), ev.end(), [](auto &l, auto &r) { return l.x < r.x; });
    ll Y = y.back().first - y[0].first;
    lazy_segtree<RU::T, RU::op, RU::e, RU::F, RU::fx, RU::fg, RU::id> S(dy);
    ll ans = 0;
    for(ll i = 0, cx = 0; i < 2 * N; i++) {
      auto [x, ly, ry, add] = ev[i];
      auto [m, cm] = S.all_prod();
      ll dx = x - cx;
      ans += m ? Y * dx : (Y - cm) * dx;
      cx = x;
      add ? S.apply(ly, ry, 1) : S.apply(ly, ry, -1);
    }
    return ans;
  }
};
