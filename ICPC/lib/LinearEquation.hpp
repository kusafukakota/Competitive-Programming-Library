#pragma once

#include <lib/GaussianElimination.hpp>

template<typename T> Matrix<T> LinearEquation(Matrix<T> a, vector<T> b) {
  int H = a.size(), W = a[0].size();
  for(int i = 0; i < H; i++) { a[i].emplace_back(b[i]); }
  auto p = GaussianElimination(a, W, true);
  int rank = p.first;
  for(int i = rank; i < H; i++) {
    if(a[i][W] == 0) { return Matrix<T>{}; }
  }
  Matrix<T> res(1, W);
  vector<int> pivot(W, -1);
  for(int i = 0, j = 0; i < rank; i++) {
    while(a[i][j] == 0) { j++; }
    res[0][j] = a[i][W];
    pivot[j] = i;
  }
  for(int j = 0; j < W; j++) {
    if(pivot[j] == -1) {
      vector<T> x(W);
      x[j] = 1;
      for(int k = 0; k < j; k++) {
        if(pivot[k] != -1) { x[k] = -a[pivot[k]][j]; }
      }
      res.emplace_back(x);
    }
  }
  return res;
}