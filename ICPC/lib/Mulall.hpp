#pragma once

#include <atcoder/convolution>
using namespace atcoder;

auto mulall(vector<auto> &v) {
  queue<int> q;
  for(int i = 0; i < (int)v.size(); i++) { q.emplace(i); }
  while((int)q.size() >= 2) {
    int x = q.front();
    q.pop();
    int y = q.front();
    q.pop();
    v[x] = convolution(v[x], v[y]);
    q.emplace(x);
  }
  return v[q.front()];
}