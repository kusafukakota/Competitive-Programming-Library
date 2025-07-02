#pragma once

#include <atcoder/dsu>
using namespace atcoder;

template<typename T> vector<tuple<T, int, int>> ManhattanMST(vector<T> &xs, vector<T> &ys) {
  const int N = xs.size();
  vector<int> idx(N);
  iota(idx.begin(), idx.end(), 0);
  vector<tuple<T, int, int>> tmp, ret;
  for(int s = 0; s < 2; s++) {
    for(int t = 0; t < 2; t++) {
      ranges::sort(idx, [&](int i, int j) { return xs[i] + ys[i] < xs[j] + ys[j]; });
      map<T, int> sweep;
      for(auto &i : idx) {
        for(auto it = sweep.lower_bound(-ys[i]); it != sweep.end(); it = sweep.erase(it)) {
          int j = it->second;
          if(xs[i] - xs[j] < ys[i] - ys[j]) { break; }
          tmp.emplace_back(abs(xs[i] - xs[j]) + abs(ys[i] - ys[j]), i, j);
        }
        sweep[-ys[i]] = i;
      }
      swap(xs, ys);
    }
    for(auto &x : xs) { x = -x; }
  }
  ranges::sort(tmp);
  dsu u(N);
  for(auto &[w, a, b] : tmp) {
    if(u.same(a, b)) { continue; }
    u.merge(a, b);
    ret.emplace_back(w, a, b);
  }
  return ret;
}