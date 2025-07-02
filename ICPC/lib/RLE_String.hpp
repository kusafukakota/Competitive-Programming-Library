#pragma once

vector<pair<char, ll>> RLE(const string &s) {
  int p = -1, n = s.size();
  vector<pair<char, ll>> r;
  for(int i = 0; i < n - 1; i++) {
    if(s[i] != s[i + 1]) {
      r.emplace_back(s[i], i - p);
      p = i;
    }
  }
  if(!s.empty()) { r.emplace_back(s.back(), n - 1 - p); }
  return r;
}