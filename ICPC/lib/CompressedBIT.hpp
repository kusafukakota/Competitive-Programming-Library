#pragma once

#include <atcoder/fenwicktree>
using namespace atcoder;

template<typename S, typename T> struct CompressedBIT {
 private:
  fenwick_tree<T> f;
  vector<S> p;
  int id(S x) const { return ranges::lower_bound(p, x) - p.begin(); }

 public:
  CompressedBIT() = default;
  CompressedBIT(int N) { p.reserve(N); }
  void use(S x) { p.emplace_back(x); }
  void build() {
    ranges::sort(p);
    p.erase(unique(p.begin(), p.end()), p.end());
    f = fenwick_tree<T>(p.size());
  }
  void add(S i, T x) { f.add(id(i), x); }
  T sum(S l, S r) { return f.sum(id(l), id(r)); }
};
