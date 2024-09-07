template<typename T> vector<ll> LIS(const vector<T> &v, bool strict = true) {
  vector<T> lis;
  vector<ll> pos;
  for(const auto &i : v) {
    auto it = (strict ? ranges::lower_bound(lis, i) : ranges::upper_bound(lis, i));
    pos.emplace_back(it - lis.begin());
    it == lis.end() ? lis.emplace_back(i) : *it = i;
  }
  vector<ll> idx(lis.size());
  ll i = (int)idx.size() - 1, p = (int)pos.size() - 1;
  while(i >= 0 && p >= 0) {
    if(pos[p] == i) { idx[i--] = p; }
    p--;
  }
  return idx;
}
