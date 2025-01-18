template<typename T> pair<ll, T> GaussianElimination(Matrix<T> &v, ll pivot_end = -1, bool diagonalize = false) {
  int H = v.size(), W = v[0].size(), rank = 0;
  if(pivot_end == -1) { pivot_end = W; }
  T det = 1;
  for(int j = 0; j < pivot_end; j++) {
    int idx = -1;
    for(int i = rank; i < H; i++) {
      if(v[i][j] != T(0)) {
        idx = i;
        break;
      }
    }
    if(idx == -1) {
      det = 0;
      continue;
    }
    if(rank != idx) {
      det = -det;
      swap(v[rank], v[idx]);
    }
    det *= v[rank][j];
    if(diagonalize && v[rank][j] != T(1)) {
      T c = T(1) / v[rank][j];
      for(int k = j; k < W; k++) { v[rank][k] *= c; }
    }
    int is = diagonalize ? 0 : rank + 1;
    for(int i = is; i < H; i++) {
      if(i == rank) { continue; }
      if(v[i][j] != T(0)) {
        T c = v[i][j] / v[rank][j];
        for(int k = j; k < W; k++) { v[i][k] -= v[rank][k] * c; }
      }
    }
    rank++;
  }
  return make_pair(rank, det);
}
