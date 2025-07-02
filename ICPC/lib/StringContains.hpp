#pragma once

#include <atcoder/string>
using namespace atcoder;

// return S⊃T
bool contains(const string &s, const string &t) {
  int n = s.size(), m = t.size();
  auto z = z_algorithm(t + s);
  for(int i = m; i <= n; i++) {
    if(z[i] >= m) { return true; }
  }
  return false;
}