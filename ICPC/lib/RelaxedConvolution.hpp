#pragma once

#include <atcoder/convolution>
using namespace atcoder;

struct RelaxedConvolution {
  vector<mint> a, b, c;
  ll k;
  RelaxedConvolution(ll n): a(n), b(n), c(n), k(0) {}
  mint operator()(mint na, mint nb) {
    a[k] = na;
    b[k] = nb;
    ll s = k + 2;
    for(ll w = 1; s % w == 0 && w < s; w <<= 1) {
      for(ll r = 0; r < 2; r++) {
        if(r == 0 || w * 2 != s) {
          vector<mint> f(w), g(w);
          for(ll i = 0; i < w; i++) { f[i] = a[w - 1 + i], g[i] = b[k - w + 1 + i]; }
          f = convolution(f, g);
          for(ll i = 0, j = k; i < (ll)f.size() && j < (ll)c.size(); i++, j++) { c[j] += f[i]; }
        }
        swap(a, b);
      }
    }
    return c[k++];
  }
};