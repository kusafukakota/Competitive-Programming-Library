#pragma once

#include <lib/DivisorTransform.hpp>

template<typename T> vector<T> LcmConvolution(const vector<T> &a, const vector<T> &b) {
  assert(a.size() == b.size());
  auto s = a, t = b;
  DivisorTransform::ZetaTransform(s);
  DivisorTransform::ZetaTransform(t);
  for(int i = 0; i < (int)a.size(); i++) { s[i] *= t[i]; }
  DivisorTransform::MobiusTransform(s);
  return s;
}