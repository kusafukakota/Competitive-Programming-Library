#pragma once

template<typename T> vector<pair<T, ll>> RLE(const vector<T> &v) {
  int p = -1, n = v.size();
  vector<pair<T, ll>> r;
  for(int i = 0; i < n - 1; i++) {
    if(v[i] != v[i + 1]) {
      r.emplace_back(v[i], i - p);
      p = i;
    }
  }
  if(!v.empty()) { r.emplace_back(v.back(), n - 1 - p); }
  return r;
}