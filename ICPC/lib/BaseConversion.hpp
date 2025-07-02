#pragma once

vector<ll> Base(ll x, ll n, bool re = false) {
  vector<ll> r;
  while(x) {
    r.emplace_back(x % n);
    x /= n;
  }
  if(re) { ranges::reverse(r); }
  return r;
}