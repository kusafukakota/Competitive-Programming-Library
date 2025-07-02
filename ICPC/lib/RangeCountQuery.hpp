#pragma once

template<typename T> struct RangeCountQuery {
  int N;
  vector<vector<ll>> idx;
  RangeCountQuery() {};
  RangeCountQuery(const vector<T> &v): N(ranges::max(v) + 1), idx(N) {
    for(int i = 0; i < (int)v.size(); i++) { idx[v[i]].emplace_back(i); }
  }
  int query(int l, int r, int x) {
    if(l >= r || x < 0 || x > N) { return 0; }
    return ranges::lower_bound(idx[x], r) - ranges::lower_bound(idx[x], l);
  }
};