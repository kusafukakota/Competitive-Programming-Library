#pragma once

#include <atcoder/math>
using namespace atcoder;

struct Barrett {
  using ull = unsigned long long;
  unsigned m;
  ull im;
  Barrett(): m(), im() {}
  Barrett(int n): m(n), im(ull(-1) / m + 1) {}
  constexpr inline ll quo(ull n) {
    ull x = ull((__uint128_t(n) * im) >> 64);
    unsigned r = n - x * m;
    return m <= r ? x - 1 : x;
  }
  constexpr inline ll rem(ull n) {
    ull x = ull((__uint128_t(n) * im) >> 64);
    unsigned r = n - x * m;
    return m <= r ? r + m : r;
  }
  constexpr inline pair<ll, int> quorem(ull n) {
    ull x = ull((__uint128_t(n) * im) >> 64);
    unsigned r = n - x * m;
    if(m <= r) { return {x - 1, r + m}; }
    return {x, r};
  }
  constexpr inline ll pow(ull n, ll p) {
    unsigned a = rem(n), r = m == 1 ? 0 : 1;
    while(p) {
      if(p & 1) { r = rem(ull(r) * a); }
      a = rem(ull(a) * a);
      p >>= 1;
    }
    return r;
  }
};

struct PrimePowerBinomial {
  int p, q, M;
  vector<int> fac, finv, inv;
  int delta;
  Barrett bm, bp;

  PrimePowerBinomial(int _p, int _q): p(_p), q(_q) {
    assert(1 < p && p <= (1LL << 30) - 1);
    assert(_q > 0);
    ll m = 1;
    while(_q--) {
      m *= p;
      assert(m <= (1LL << 30) - 1);
    }
    M = m;
    bm = Barrett(M), bp = Barrett(p);
    enumerate();
    delta = (p == 2 && q >= 3) ? 1 : M - 1;
  }
  void enumerate() {
    int MX = min<int>(M, 20000010);
    fac.resize(MX);
    finv.resize(MX);
    inv.resize(MX);
    fac[0] = finv[0] = inv[0] = 1;
    fac[1] = finv[1] = inv[1] = 1;
    for(int i = 2; i < MX; i++) {
      if(i % p == 0) {
        fac[i] = fac[i - 1];
        fac[i + 1] = bm.rem(1LL * fac[i - 1] * (i + 1));
        i++;
      }
      else { fac[i] = bm.rem(1LL * fac[i - 1] * i); }
    }
    finv[MX - 1] = bm.pow(fac[MX - 1], M / p * (p - 1) - 1);
    for(int i = MX - 2; i > 1; --i) {
      if(i % p == 0) {
        finv[i] = bm.rem(1LL * finv[i + 1] * (i + 1));
        finv[i - 1] = finv[i];
        i--;
      }
      else { finv[i] = bm.rem(1LL * finv[i + 1] * (i + 1)); }
    }
  }

  ll Lucas(ll n, ll m) {
    int res = 1;
    while(n) {
      int n0, m0;
      tie(n, n0) = bp.quorem(n);
      tie(m, m0) = bp.quorem(m);
      if(n0 < m0) { return 0; }
      res = bm.rem(1LL * res * fac[n0]);
      int buf = bm.rem(1LL * finv[n0 - m0] * finv[m0]);
      res = bm.rem(1LL * res * buf);
    }
    return res;
  }

  ll C(ll n, ll m) {
    if(n < m || n < 0 || m < 0) return 0;
    if(q == 1) return Lucas(n, m);
    ll r = n - m;
    int e0 = 0, eq = 0, i = 0;
    int res = 1;
    while(n) {
      res = bm.rem(1LL * res * fac[bm.rem(n)]);
      res = bm.rem(1LL * res * finv[bm.rem(m)]);
      res = bm.rem(1LL * res * finv[bm.rem(r)]);
      n = bp.quo(n);
      m = bp.quo(m);
      r = bp.quo(r);
      int eps = n - m - r;
      e0 += eps;
      if(e0 >= q) { return 0; }
      if(++i >= q) { eq += eps; }
    }
    if(eq & 1) { res = bm.rem(1LL * res * delta); }
    res = bm.rem(1LL * res * bm.pow(p, e0));
    return res;
  }
};

// constraints:
// (M <= 1e7 and max(N) <= 1e18) or (M < 2^30 and max(N) <= 2e7)
struct ArbitraryModBinomial {
  int mod;
  vector<int> M;
  vector<PrimePowerBinomial> cs;
  ArbitraryModBinomial(ll md): mod(md) {
    assert(1 <= md);
    assert(md <= (1LL << 30) - 1);
    for(int i = 2; i * i <= md; i++) {
      if(md % i == 0) {
        int j = 0, k = 1;
        while(md % i == 0) {
          md /= i;
          j++;
          k *= i;
        }
        M.push_back(k);
        cs.emplace_back(i, j);
        assert(M.back() == cs.back().M);
      }
    }
    if(md != 1) {
      M.push_back(md);
      cs.emplace_back(md, 1);
    }
    assert(M.size() == cs.size());
  }
  ll C(ll n, ll m) {
    if(mod == 1) { return 0; }
    vector<ll> rem, d;
    for(int i = 0; i < (int)cs.size(); i++) {
      rem.push_back(cs[i].C(n, m));
      d.push_back(M[i]);
    }
    return atcoder::crt(rem, d).first;
  }
  ll operator()(ll n, ll m) { return C(n, m); }
};