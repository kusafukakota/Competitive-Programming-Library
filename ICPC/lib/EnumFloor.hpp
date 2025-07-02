#pragma once

// i∈[l, r) ⇔ ⌊N / i⌋ = q
vector<tuple<ll, ll, ll>> EnumFloor(ll n) {
  vector<tuple<ll, ll, ll>> ret;
  ll l = 1;
  while(l <= n) {
    ll q = n / l, r = n / q + 1;
    ret.push_back({l, r, q});
    l = r;
  }
  return ret;
}