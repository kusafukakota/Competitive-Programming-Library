#pragma once

#include <atcoder/string>
using namespace atcoder;

template<typename T> int ShortestRepetition(const vector<T> &v) {
  vector<int> z = z_algorithm(v);
  int sz = v.size();
  for(int i = 1; i < sz; i++) {
    if(z[i] == sz - i && sz % i == 0) { return i; }
  }
  return sz;
}