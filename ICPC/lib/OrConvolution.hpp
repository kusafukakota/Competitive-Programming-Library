#pragma once

#include <lib/SubsetTransform.hpp>

template<typename T> vector<T> OrConvolution(vector<T> a, vector<T> b) {
  const int n = a.size();
  assert(a.size() == b.size());
  assert(!(n & (n - 1)));
  SubsetTransform::ZetaTransform(a);
  SubsetTransform::ZetaTransform(b);
  for(int i = 0; i < n; i++) { a[i] *= b[i]; }
  SubsetTransform::MobiusTransform(a);
  return a;
}