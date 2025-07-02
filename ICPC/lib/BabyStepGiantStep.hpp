#pragma once

// n : 周期, m : √n, fm : f^m
template<typename T> ll BSGS(T s, T g, ll n, ll m, const auto &f, const auto &fm) {
  unordered_map<T, int> mp;
  for(int i = 1; i <= m; i++) {
    g = f(g);
    mp[g] = -i;
  }
  for(int i = 1;; i++) {
    s = fm(s);
    if(mp.count(s)) { return m * i + mp[s]; }
    if(n <= m * i) { return -1; }
  }
}