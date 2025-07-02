#pragma once

#include <lib/MultipleTransform.hpp>

template<typename T> vector<T> GcdConvolution(const vector<T> &a, const vector<T> &b) {
  assert(a.size() == b.size());
  auto s = a, t = b;
  MultipleTransform::ZetaTransform(s);
  MultipleTransform::ZetaTransform(t);
  for(int i = 0; i < (int)a.size(); i++) { s[i] *= t[i]; }
  MultipleTransform::MobiusTransform(s);
  return s;
}