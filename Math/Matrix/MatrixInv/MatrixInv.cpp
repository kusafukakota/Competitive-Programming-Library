template<typename T> Matrix<T> Matinv(const Matrix<T> &v) {
  int N = v.size();
  assert(N > 0);
  assert(N == (int)v[0].size());

  Matrix<T> m(N, 2 * N);
  for(int i = 0; i < N; i++) {
    ranges::copy(v[i], m[i].begin());
    m[i][N + i] = 1;
  }
  auto [rank, det] = GaussianElimination(m, N, true);
  if(rank != N) { return {}; }

  Matrix<T> b(N, 0);
  for(int i = 0; i < N; i++) {
    copy(m[i].begin() + N, m[i].end(), back_inserter(b[i]));
  }
  return b;
}
