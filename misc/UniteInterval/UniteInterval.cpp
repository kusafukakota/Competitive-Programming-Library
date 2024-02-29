template<typename T> vector<pair<T, T>> UniteInterval(const vector<pair<T, T>> &v) {
  vector<pair<T, T>> u{v}, r;
  ranges::sort(u);
  for(auto &p : u) {
    r.emplace_back(p);
    while((ll)r.size() >= 2) {
      ll n = r.size();
      if(r[n - 2].second < r[n - 1].first) { break; }
      pair<T, T> q;
      q.first = r[n - 2].first;
      q.second = max<T>(r[n - 2].second, r[n - 1].second);
      r.pop_back();
      r.pop_back();
      r.emplace_back(q);
    }
  }
  return r;
}
