#pragma once

template<size_t N> bool operator<(const bitset<N> &a, const bitset<N> &b) {
  int f = (a ^ b)._Find_first();
  return f == N ? false : a[f];
}

template<size_t H_MAX, size_t W_MAX> struct F2_Matrix {
  int H, W;
  array<bitset<W_MAX>, H_MAX> A;
  F2_Matrix(int h = H_MAX, int w = W_MAX): H(h), W(w) {
    assert(h >= 0 && h <= (int)(H_MAX));
    assert(w >= 0 && w <= (int)(W_MAX));
    for(int i = 0; i < (int)H_MAX; i++) { A[i].reset(); }
  }
  inline bitset<W_MAX> &operator[](int i) { return A[i]; }
  inline const bitset<W_MAX> &operator[](int i) const { return A[i]; }
  static F2_Matrix I(int n) {
    F2_Matrix a(n, n);
    for(int i = 0; i < n; i++) { a[i][i] = true; }
    return a;
  }
  F2_Matrix &operator*=(const F2_Matrix &B) {
    F2_Matrix C(H, B.W);
    for(int i = 0; i < H; i++) {
      for(int j = 0; j < W; j++) {
        if(A[i][j]) { C[i] ^= B[j]; }
      }
    }
    swap(A, C.A);
    return *this;
  }
  F2_Matrix operator*(const F2_Matrix &B) const { return F2_Matrix(*this) *= B; }
  friend F2_Matrix and_or_product(const F2_Matrix &A, const F2_Matrix &B) {
    F2_Matrix C(A.H, B.W);
    for(int i = 0; i < A.H; i++) {
      for(int j = 0; j < A.W; j++) {
        if(A[i][j]) { C[i] |= B[j]; }
      }
    }
    return C;
  }
  int sweep(ll wr = -1) {
    if(wr == -1) { wr = W; }
    int t = 0;
    for(int u = 0; u < wr; u++) {
      int piv = -1;
      for(int i = t; i < H; i++) {
        if(A[i][u]) {
          piv = i;
          break;
        }
      }
      if(piv == -1) { continue; }
      if(piv != t) { swap(A[piv], A[t]); }
      for(int i = 0; i < H; i++) {
        if(i != t && A[i][u]) { A[i] ^= A[t]; }
      }
      t++;
    }
    return t;
  }
  F2_Matrix inv() const {
    assert(H == W);
    int N = H;
    F2_Matrix<H_MAX, W_MAX * 2> c(H, W * 2);
    for(int i = 0; i < N; i++) {
      c[i][i + N] = 1;
      for(int j = 0; j < N; j++) { c[i][j] = A[i][j]; }
    }
    int r = c.sweep();
    assert(r == N);
    F2_Matrix b(H, W);
    for(int i = 0; i < N; i++) {
      for(int j = 0; j < N; j++) { b[i][j] = c[i][i + N]; }
    }
    return b;
  }
  bool operator<(const F2_Matrix &rhs) const {
    if(H != rhs.H) { return H < rhs.H; }
    if(W != rhs.W) { return W < rhs.W; }
    return A < rhs.A;
  }
  bool operator==(const F2_Matrix &rhs) const {
    return H == rhs.H && W == rhs.W && A == rhs.A;
  }
  friend ostream &operator<<(ostream &os, const F2_Matrix &b) {
    for(int i = 0; i < b.H; i++) {
      os << "[ ";
      for(int j = 0; j < b.W; j++) { os << b[i][j] << ", "; }
      os << "],\n";
    }
    return os;
  }
};