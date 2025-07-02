#pragma once

#include <lib/Binomial.hpp>
#include <lib/FormalPowerSeries.hpp>

FPS Stirling2(int N) {
  FPS f(N + 1), g(N + 1);
  for(int i = 0; i <= N; i++) {
    f[i] = mint(i).pow(N) * C(-i);
    g[i] = i & 1 ? -C(-i) : C(-i);
  }
  return (f * g).pre(N + 1);
}