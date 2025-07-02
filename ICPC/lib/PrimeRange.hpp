#pragma once

#include <lib/PrimeEnum.hpp>
#include <lib/Root.hpp>

vector<vector<pair<ll, ll>>> PrimeRange(ll l, ll r) {
  int n = r - l + 1;
  vector<ll> v(n);
  iota(v.begin(), v.end(), l);
  vector<vector<pair<ll, ll>>> p(n);
  for(auto &i : PrimeEnum(Root(r))) {
    for(ll j = (l + i - 1) / i * i; j <= r; j += i) {
      int c = 0;
      while(v[j - l] % i == 0) {
        v[j - l] /= i;
        c++;
      }
      if(c) { p[j - l].emplace_back(i, c); }
    }
  }
  for(int i = 0; i < n; i++) {
    if(v[i] != 1) { p[i].emplace_back(v[i], 1); }
  }
  return p;
}