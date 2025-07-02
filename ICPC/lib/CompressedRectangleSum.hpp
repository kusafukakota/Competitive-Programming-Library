#pragma once

#include <atcoder/fenwicktree>
using namespace atcoder;

template<typename S, typename T> struct CompressedRectangleSum {
  struct P {
    S x, y;
    T w;
  };
  struct Q1 {
    S lx, ly, rx, ry;
  };
  vector<P> ps;
  vector<Q1> Qs;
  CompressedRectangleSum() = default;
  CompressedRectangleSum(int N, int Q) {
    ps.reserve(N);
    Qs.reserve(Q);
  }
  void add(S x, S y, T w) { ps.emplace_back(P{x, y, w}); }
  void sum(S lx, S rx, S ly, S ry) { Qs.emplace_back(Q1{lx, ly, rx, ry}); }
  vector<T> solve() {
    int N = ps.size(), Q = Qs.size();
    ranges::sort(ps, [](const P &a, const P &b) { return a.y < b.y; });
    vector<S> ys;
    ys.reserve(N);
    for(P &p : ps) {
      if(ys.empty() || ys.back() != p.y) { ys.emplace_back(p.y); }
      p.y = ys.size() - 1;
    }
    ys.shrink_to_fit();
    struct Q2 {
      S x, ly, ry;
      bool type;
      int idx;
    };
    vector<Q2> qs;
    qs.reserve(Q + Q);
    for(int i = 0; i < Q; i++) {
      auto &q = Qs[i];
      int d = ranges::lower_bound(ys, q.ly) - ys.begin(), u = ranges::lower_bound(ys, q.ry) - ys.begin();
      qs.emplace_back(Q2{q.lx, d, u, false, i});
      qs.emplace_back(Q2{q.rx, d, u, true, i});
    }
    ranges::sort(ps, [](const P &a, const P &b) { return a.x < b.x; });
    ranges::sort(qs, [](const Q2 &a, const Q2 &b) { return a.x < b.x; });
    vector<T> ans(Q);
    int j = 0;
    fenwick_tree<T> f(ys.size());
    for(auto &q : qs) {
      while(j < N && ps[j].x < q.x) {
        f.add(ps[j].y, ps[j].w);
        j++;
      }
      if(q.type) { ans[q.idx] += f.sum(q.ly, q.ry); }
      else { ans[q.idx] -= f.sum(q.ly, q.ry); }
    }
    return ans;
  }
};
