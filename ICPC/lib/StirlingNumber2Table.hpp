#pragma once

template<typename T> vector<vector<T>> Stirling2(int N) {
  vector<vector<T>> r(N + 1, vector<T>(N + 1, 0));
  r[0][0] = 1;
  for(int i = 1; i <= N; i++) {
    for(int j = 1; j <= i; j++) { r[i][j] = r[i - 1][j - 1] + r[i - 1][j] * j; }
  }
  return r;
}