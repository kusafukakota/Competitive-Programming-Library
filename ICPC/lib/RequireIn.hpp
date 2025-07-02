#pragma once

#include <atcoder/scc>
using namespace atcoder;

template<typename T> int RequireIn(vector<vector<T>> &g_) {
  int N = g_.size();
  scc_graph s(N);
  vector<vector<int>> g(N);
  for(int i = 0; i < N; i++) {
    for(auto &j : g_[i]) {
      s.add_edge(i, j);
      g[j].emplace_back(i);
    }
  }
  auto scc = s.scc();
  for(auto &i : scc) { ranges::sort(i); }
  int r = 0;
  for(auto &i : scc) {
    bool in = false;
    for(auto &j : i) {
      for(auto &k : g[j]) {
        if(!ranges::binary_search(i, k)) {
          in = true;
          break;
        }
      }
      if(in) { break; }
    }
    if(!in) { r++; }
  }
  return r;
}