#pragma once

#include <lib/TaylorShift.hpp>

FPS Stirling1(int N) {
  if(N <= 0) { return {1}; }
  int lg = 31 - __builtin_clz(N);
  FPS f{0, 1};
  for(int i = lg - 1; i >= 0; i--) {
    int n = N >> i;
    f *= TaylorShift(f, mint(n >> 1));
    if(n & 1) { f = (f << 1) + f * (n - 1); }
  }
  return f;
}