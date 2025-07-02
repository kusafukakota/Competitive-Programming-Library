#pragma once

#include <lib/Binomial.hpp>

template<typename T> mint LagrangePolynomial(vector<T> &v, ll x) {
  ll N = v.size() - 1;
  mint r = 0;
  if(x <= N) { return v[x]; }
  vector<mint> dp(N + 1, 1), pd(N + 1, 1);
  for(ll i = 0; i < N; i++) { dp[i + 1] = dp[i] * (x - i); }
  for(ll i = N; i >= 1; i--) { pd[i - 1] = pd[i] * (x - i); }
  for(ll i = 0; i <= N; i++) {
    mint t = dp[i] * pd[i] * C(-i) * C(i - N) * v[i];
    r += (N - i) & 1 ? -t : t;
  }
  return r;
}