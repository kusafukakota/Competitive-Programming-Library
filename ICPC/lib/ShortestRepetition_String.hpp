#pragma once

#include <atcoder/string>
using namespace atcoder;

int ShortestRepetition(const string &s) {
  vector<int> z = z_algorithm(s);
  int sz = s.size();
  for(int i = 1; i < sz; i++) {
    if(z[i] == sz - i && sz % i == 0) { return i; }
  }
  return sz;
}