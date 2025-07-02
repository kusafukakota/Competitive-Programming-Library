#pragma once

template<typename T> struct CompressedRangeCountQuery {
  vector<T> v;
  vector<vector<ll>> idx;
  CompressedRangeCountQuery() {}
  CompressedRangeCountQuery(const vector<T> &v_): v(v_) {
    ranges::sort(v);
    v.erase(unique(v.begin(), v.end()), v.end());
    idx.resize(v.size());
    for(int i = 0; i < (int)v_.size(); i++) { idx[ranges::lower_bound(v, v_[i]) - v.begin()].emplace_back(i); }
  }
  int query(int l, int r, T x) {
    if(l >= r || !ranges::binary_search(v, x)) { return 0; }
    x = ranges::lower_bound(v, x) - v.begin();
    return ranges::lower_bound(idx[x], r) - ranges::lower_bound(idx[x], l);
  }
};