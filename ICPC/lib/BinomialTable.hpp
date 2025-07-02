#pragma once

template<typename T> vector<vector<T>> BinomialTable(int n) {
  vector<vector<T>> r(n + 1, vector<T>(n + 1, 0));
  for(int i = 0; i <= n; i++) {
    for(int j = 0; j <= i; j++) {
      if(j == 0 || j == i) { r[i][j] = 1; }
      else { r[i][j] = r[i - 1][j - 1] + r[i - 1][j]; }
    }
  }
  return r;
}