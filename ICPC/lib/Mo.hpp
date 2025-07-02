#pragma once

struct Mo {
  int N, Q, W;
  vector<int> L, R, O;
  bool built;

 private:
  void sort() {
    vector<int> c(N + 1), buf(Q);
    for(int i = 0; i < Q; i++) { c[R[i]]++; }
    for(int i = 1; i < (int)c.size(); i++) { c[i] += c[i - 1]; }
    for(int i = 0; i < Q; i++) { buf[--c[R[i]]] = i; }
    vector<int> b(Q);
    for(int i = 0; i < Q; i++) { b[i] = L[i] / W; }
    c.resize(N / W + 1);
    ranges::fill(c, 0);
    for(int i = 0; i < Q; i++) { c[b[i]]++; }
    for(int i = 1; i < (int)c.size(); i++) { c[i] += c[i - 1]; }
    for(int i = 0; i < Q; i++) { O[--c[b[buf[i]]]] = buf[i]; }
    for(int i = 0, j = 0; i < Q; i = j) {
      int bi = b[O[i]];
      j = i + 1;
      while(j != Q && bi == b[O[j]]) { j++; }
      if(~bi & 1) { reverse(O.begin() + i, O.begin() + j); }
    }
  }
  int dist(int i, int j) { return abs(L[i] - L[j]) + abs(R[i] - R[j]); }
  void climb(int it = 3, int interval = 5) {
    vector<int> d(Q - 1);
    for(int i = 0; i < Q - 1; i++) { d[i] = dist(O[i], O[i + 1]); }
    while(it--) {
      for(int i = 1; i < Q; i++) {
        int pre1 = d[i - 1], js = i + 1, je = min<int>(i + interval, Q - 1);
        for(int j = je - 1; j >= js; j--) {
          int pre2 = d[j], now1 = dist(O[i - 1], O[j]), now2 = dist(O[i], O[j + 1]);
          if(now1 + now2 < pre1 + pre2) {
            reverse(O.begin() + i, O.begin() + j + 1);
            reverse(d.begin() + i, d.begin() + j);
            d[i - 1] = pre1 = now1;
            d[j] = now2;
          }
        }
      }
    }
  }

 public:
  Mo(int n, int q): N(n), Q(q), O(Q), built(false) {
    W = max<int>(1, 1.0 * N / max<double>(1.0, sqrt(Q / 2.0)));
    iota(O.begin(), O.end(), 0);
  }
  // [l, r)
  void insert(int l, int r) {
    assert(0 <= l && l <= r && r <= N);
    L.push_back(l);
    R.push_back(r);
  }
  void build() {
    sort();
    climb();
    built = true;
  }
  template<typename AL, typename AR, typename DL, typename DR, typename REM>
  void solve(const AL &add_l, const AR &add_r, const DL &del_l, const DR &del_r, const REM &rem) {
    if(!built) { build(); }
    int nl = 0, nr = 0;
    for(auto idx : O) {
      while(nl > L[idx]) { add_l(--nl); }
      while(nr < R[idx]) { add_r(nr++); }
      while(nl < L[idx]) { del_l(nl++); }
      while(nr > R[idx]) { del_r(--nr); }
      rem(idx);
    }
  }
  template<typename A, typename D, typename REM>
  void solve(const A &add, const D &del, const REM &rem) { solve(add, add, del, del, rem); }
};