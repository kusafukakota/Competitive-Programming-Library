#pragma once

template<typename T, bool isMin> struct ConvexHullTrick {
 private:
  deque<pair<T, T>> H;
  static constexpr int sgn(T x) { return x == 0 ? 0 : (x < 0 ? -1 : 1); }
  static constexpr T floor(T n, T d) { return n / d - ((n ^ d) < 0 && n % d); }
  static constexpr bool check(const pair<T, T> &a, const pair<T, T> &b, const pair<T, T> &c) {
    if(b.second == a.second || c.second == b.second) { return sgn(b.first - a.first) * sgn(c.second - b.second) >= sgn(c.first - b.first) * sgn(b.second - a.second); }
    if constexpr(is_integral<T>::value) { return floor(b.second - a.second, a.first - b.first) >= floor(c.second - b.second, b.first - c.first); }
    else { return (b.first - a.first) * sgn(c.second - b.second) / abs(b.second - a.second) >= (c.first - b.first) * sgn(b.second - a.second) / abs(c.second - b.second); }
  }
  static constexpr T get(const pair<T, T> &a, const T &x) { return a.first * x + a.second; }

 public:
  ConvexHullTrick() = default;
  bool empty() const { return H.empty(); }
  void clear() { H.clear(); }
  // 直線 y = ax + b を追加（a は広義単調増加/減少） O(N) in total
  void add(T a, T b) {
    if(!isMin) { a *= -1, b *= -1; }
    pair<T, T> line(a, b);
    if(empty()) {
      H.emplace_front(line);
      return;
    }
    if(H.front().first <= a) {
      if(H.front().first == a) {
        if(H.front().second <= b) { return; }
        H.pop_front();
      }
      while(H.size() >= 2 && check(line, H.front(), H[1])) { H.pop_front(); }
      H.emplace_front(line);
    }
    else {
      assert(a <= H.back().first);
      if(H.back().first == a) {
        if(H.back().second <= b) { return; }
        H.pop_back();
      }
      while(H.size() >= 2 && check(H[H.size() - 2], H.back(), line)) { H.pop_back(); }
      H.emplace_back(line);
    }
  }
  // ax + b の最大値/最小値を返す O(log N)
  T query(T x) const {
    assert(!empty());
    int l = -1, r = H.size() - 1;
    while(l + 1 < r) {
      int m = (l + r) >> 1;
      get(H[m], x) >= get(H[m + 1], x) ? l = m : r = m;
    }
    return isMin ? get(H[r], x) : -get(H[r], x);
  }
  // ax + b の最大値/最小値を返す（x は単調増加）O(N + Q) in total
  T query_inc(T x) {
    assert(!empty());
    while(H.size() >= 2 && get(H.front(), x) >= get(H[1], x)) { H.pop_front(); }
    return isMin ? get(H.front(), x) : -get(H.front(), x);
  }
  // ax + b の最大値/最小値を返す（x は単調減少）O(N + Q) in total
  T query_dec(T x) {
    assert(!empty());
    while(H.size() >= 2 && get(H.back(), x) >= get(H[H.size() - 2], x)) { H.pop_back(); }
    return isMin ? get(H.back(), x) : -get(H.back(), x);
  }
};
