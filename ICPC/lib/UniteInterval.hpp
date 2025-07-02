#pragma once

// union of [a1,b1), [a2,b2) ...
template<typename T> vector<pair<T, T>> UniteInterval(const vector<pair<T, T>> &v) {
  vector<pair<T, T>> u{v}, r;
  ranges::sort(u);
  for(auto &p : u) {
    r.emplace_back(p);
    while((int)r.size() >= 2) {
      const int n = r.size();
      if(r[n - 2].second < r[n - 1].first) { break; }
      pair<T, T> q = {r[n - 2].first, max<T>(r[n - 2].second, r[n - 1].second)};
      r.pop_back();
      r.pop_back();
      r.emplace_back(q);
    }
  }
  return r;
}