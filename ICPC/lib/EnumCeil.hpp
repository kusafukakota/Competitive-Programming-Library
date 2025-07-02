#pragma once

// i∈[l, r) ⇔ ⌈N / i⌉ = q
vector<tuple<ll, ll, ll>> EnumCeil(ll n) {
  vector<tuple<ll, ll, ll>> ret;
  ll l = 1;
  while(l <= n) {
    ll q = (n + l - 1) / l, r = n + 1;
    if(q != 1) { r = (n - 1) / (q - 1) + 1; }
    ret.push_back({l, r, q});
    l = r;
  }
  return ret;
}