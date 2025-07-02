#pragma once

#include <lib/SupersetTransform.hpp>

template<typename T> vector<T> AndConvolution(vector<T> a, vector<T> b) {
  const int n = a.size();
  assert(a.size() == b.size());
  assert(!(n & (n - 1)));
  SupersetTransform::ZetaTransform(a);
  SupersetTransform::ZetaTransform(b);
  for(int i = 0; i < n; i++) { a[i] *= b[i]; }
  SupersetTransform::MobiusTransform(a);
  return a;
}