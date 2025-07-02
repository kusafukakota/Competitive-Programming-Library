#pragma once

template<typename T> vector<T> Compress(vector<T> &v) {
  vector<T> r = v;
  ranges::sort(r);
  r.erase(unique(r.begin(), r.end()), r.end());
  for(auto &i : v) { i = ranges::lower_bound(r, i) - r.begin(); }
  return r;
}