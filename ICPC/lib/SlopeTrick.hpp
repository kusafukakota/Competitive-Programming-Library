#pragma once

// https://ei1333.github.io/library/structure/others/slope-trick.hpp
struct SlopeTrick {
  ll min_f, add_l, add_r;
  priority_queue<ll> L;
  priority_queue<ll, vector<ll>, greater<ll>> R;

 private:
  void push_R(const ll &a) { R.emplace(a - add_r); }
  ll top_R() const { return R.empty() ? 1e18 : R.top() + add_r; }
  ll pop_R() {
    ll val = top_R();
    if(!R.empty()) { R.pop(); }
    return val;
  }
  void push_L(const ll &a) { L.emplace(a - add_l); }
  ll top_L() const { return L.empty() ? -1e18 : L.top() + add_l; }
  ll pop_L() {
    ll val = top_L();
    if(!L.empty()) { L.pop(); }
    return val;
  }
  size_t size() { return L.size() + R.size(); }

 public:
  SlopeTrick(): min_f(0), add_l(0), add_r(0) {}
  struct Query {
    ll lx, rx, min_f;
  };
  Query query() const { return (Query){top_L(), top_R(), min_f}; }
  void add_all(const ll &a) { min_f += a; }
  void add_a_x(const ll &a) {
    min_f += max(0LL, a - top_R());
    push_R(a);
    push_L(pop_R());
  }
  void add_x_a(const ll &a) {
    min_f += max(0LL, top_L() - a);
    push_L(a);
    push_R(pop_L());
  }
  void add_abs(const ll &a) {
    add_a_x(a);
    add_x_a(a);
  }
  void clear_right() {
    while(!R.empty()) { R.pop(); }
  }
  void clear_left() {
    while(!L.empty()) { L.pop(); }
  }
  void shift(const ll &a, const ll &b) {
    assert(a <= b);
    add_l += a;
    add_r += b;
  }
  void shift(const ll &a) { shift(a, a); }
  ll get(const ll &x) {
    ll r = min_f;
    while(!L.empty()) { r += max(0LL, pop_L() - x); }
    while(!R.empty()) { r += max(0LL, x - pop_R()); }
    return r;
  }
  void merge(SlopeTrick &st) {
    if(st.size() > size()) {
      swap(st.L, L);
      swap(st.R, R);
      swap(st.add_l, add_l);
      swap(st.add_r, add_r);
      swap(st.min_f, min_f);
    }
    while(!st.R.empty()) { add_x_a(st.pop_R()); }
    while(!st.L.empty()) { add_a_x(st.pop_L()); }
    min_f += st.min_f;
  }
};