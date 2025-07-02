#pragma once

#include <lib/FormalPowerSeries.hpp>

// 1^i + 2^i + ... + N^i  for  i∈[1,K]
FPS PowerSum(ll N, ll K) {
  FPS f{0, N + 1}, g{0, 1}, r(K + 1);
  f = f.exp(K + 2), g = g.exp(K + 2);
  f[0]--, g[0]--;
  for(ll i = 0; i <= K; i++) { f[i] = f[i + 1]; }
  for(ll i = 0; i <= K; i++) { g[i] = g[i + 1]; }
  f.pop_back(), g.pop_back();
  f /= g;
  mint fac = 1;
  for(ll i = 1; i <= K; fac *= (++i)) { r[i] = f[i] * fac; }
  return r;
}