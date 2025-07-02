#pragma once

#include <lib/PrimeFactorize.hpp>

struct Order {
 private:
  ll mod;
  size_t n;
  vector<pair<ll, ll>> fac;
  vector<ll> prod;
  ll internal_pow(ll x, ll k) const {
    ll r = 1;
    for(; k; k >>= 1) {
      if(k & 1) { r = __int128_t(r) * x % mod; }
      x = __int128_t(x) * x % mod;
    }
    return r;
  }
  int exponent(size_t i, ll x) const {
    const auto &[p, e] = fac[i];
    for(int j = 0; j < e; j++) {
      if(x == 1) { return j; }
      x = internal_pow(x, p);
    }
    return e;
  }
  ll query(size_t l, size_t r, ll x) const {
    ll res = 1;
    if(r - l == 1) {
      ll p = fac[l].first;
      int f = exponent(l, x);
      while(f--) { res *= p; }
      return res;
    }
    const size_t m = (l + r) >> 1;
    res *= query(l, m, internal_pow(x, prod[r] / prod[m]));
    res *= query(m, r, internal_pow(x, prod[m] / prod[l]));
    return res;
  }

 public:
  Order(ll p): mod(p) {
    fac = Prime(p - 1);
    n = fac.size();
    prod.resize(n + 1);
    prod[0] = 1;
    for(size_t i = 0; i < n; i++) {
      auto [pf, e] = fac[i];
      ll ppf = 1;
      while(e--) { ppf *= pf; }
      prod[i + 1] = prod[i] * ppf;
    }
  }
  ll query(ll x) const { return n ? query(0, n, x) : 0; }
  inline ll operator()(ll x) const { return query(x); }
};