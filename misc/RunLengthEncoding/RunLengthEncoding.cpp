vector<pair<char, ll>> RLE(const string &s) {
  ll p = -1, n = s.size();
  vector<pair<char, ll>> r;
  for(ll i = 0; i < n - 1; i++) {
    if(s[i] != s[i + 1]) {
      r.emplace_back(s[i], i - p);
      p = i;
    }
  }
  r.emplace_back(s.back(), n - 1 - p);
  return r;
}

template<typename T> vector<pair<T, ll>> RLE(const vector<T> &v) {
  ll p = -1, n = v.size();
  vector<pair<T, ll>> r;
  for(ll i = 0; i < n - 1; i++) {
    if(v[i] != v[i + 1]) {
      r.emplace_back(v[i], i - p);
      p = i;
    }
  }
  r.emplace_back(v.back(), n - 1 - p);
  return r;
}
