#pragma once

uint64_t Root(uint64_t a, int k = 2) {
  if(a <= 1 || k == 1) { return a; }
  if(k >= 64) { return 1; }
  auto check = [&](__uint128_t n) {
    __uint128_t x = 1, m = n;
    for(ll p = k; p; p >>= 1, m *= m) {
      if(p & 1) { x *= m; }
    }
    return x <= a;
  };
  uint64_t n = powl(a, (long double)(1.0) / k);
  while(!check(n)) { --n; }
  while(check(n + 1)) { ++n; }
  return n;
}