#pragma once

#include <lib/WalshHadamardTransform.hpp>

template<typename T> vector<T> XorConvolution(vector<T> a, vector<T> b) {
  const int n = a.size();
  assert(a.size() == b.size());
  assert(!(n & (n - 1)));
  WalshHadamardTransform(a, false);
  WalshHadamardTransform(b, false);
  for(int i = 0; i < n; i++) { a[i] *= b[i]; }
  WalshHadamardTransform(a, true);
  return a;
}