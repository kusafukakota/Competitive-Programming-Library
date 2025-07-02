#pragma once

template<typename T> vector<vector<T>> rotate(vector<vector<T>> &v) {
  ll H = v.size(), W = v[0].size();
  vector<vector<T>> u(W, vector<T>(H));
  for(int i = 0; i < H; i++) {
    for(int j = 0; j < W; j++) { u[W - j - 1][i] = v[i][j]; }
  }
  return u;
}