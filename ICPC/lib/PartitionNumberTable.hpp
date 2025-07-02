#pragma once

template<typename T> vector<vector<T>> Partition(int N) {
  vector<vector<T>> r(N + 1, vector<T>(N + 1, 0));
  for(int i = 0; i <= N; i++) { r[0][i] = 1; }
  for(int i = 1; i <= N; i++) {
    for(int j = 1; j <= N; j++) { r[i][j] = r[i][j - 1] + (i - j >= 0 ? r[i - j][j] : 0); }
  }
  return r;
}