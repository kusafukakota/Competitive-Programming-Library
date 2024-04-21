namespace SMAWKImpl {
constexpr int M = 1 << 20, N = 1 << 20;
int is0[2 * M], js0[max(2 * M, N)];
template<typename F> struct SMAWK {
  const int m, n;
  const F f;
  vector<int> v;
  SMAWK(int m, int n, F f): m(m), n(n), f(f) {
    for(int i = 0; i < m; i++) { is0[i] = i; }
    for(int j = 0; j < n; j++) { js0[j] = j; }
    v.assign(m, -1);
    rec(is0, m, js0, n);
  }
  void rec(int *is, int il, int *js, int jl) {
    if(!il || !jl) { return; }
    if(il < jl) {
      int len = 0;
      for(int y = 0; y < jl; y++) {
        const int j = js[y];
        for(; len && f(is[len - 1], js[len - 1], j); len--) {}
        if(len != il) { js[len++] = j; }
      }
      jl = len;
    }
    int *iis = is + il, *jjs = js + jl, iil = 0;
    for(int x = 1; x < il; x += 2) { iis[iil++] = is[x]; }
    for(int y = 0; y < jl; y++) { jjs[y] = js[y]; }
    rec(iis, iil, jjs, jl);
    for(int x = 0, y = 0; x < il; x += 2) {
      const int i = is[x];
      const int j1 = (x + 1 < il) ? v[is[x + 1]] : js[jl - 1];
      for(;;) {
        const int j = js[y];
        if(!~v[i] || f(i, v[i], j)) { v[i] = j; }
        if(j == j1) { break; }
        y++;
      }
    }
  }
};
}  // namespace SMAWKImpl

template<typename F> vector<int> SMAWK(int m, int n, F f) { return SMAWKImpl::SMAWK<F>(m, n, f).v; }

// C[k] = min[i+j=k] (A[i] + B[j]), A : 下に凸
template<typename T> vector<T> MinPlusConvolution(const vector<T> &A, const vector<T> &B) {
  const int a = A.size(), b = B.size();
  if(!a || !b) { return {}; }
  const auto v = SMAWK(a + b - 1, b, [&](int i, int j, int k) -> bool {
    if(i - j >= a) { return true; }
    if(i - k < 0) { return false; }
    return A[i - j] + B[j] > A[i - k] + B[k];
  });
  vector<T> C(a + b - 1);
  for(int i = 0; i < a + b - 1; i++) { C[i] = A[i - v[i]] + B[v[i]]; }
  return C;
}

// C[k] = max[i+j=k] (A[i] + B[j]), A : 上に凸
template<typename T> vector<T> MaxPlusConvolution(const vector<T> &A, const vector<T> &B) {
  const int a = A.size(), b = B.size();
  if(!a || !b) { return {}; }
  const auto v = SMAWK(a + b - 1, b, [&](int i, int j, int k) -> bool {
    if(i - j >= a) { return true; }
    if(i - k < 0) { return false; }
    return A[i - j] + B[j] < A[i - k] + B[k];
  });
  vector<T> C(a + b - 1);
  for(int i = 0; i < a + b - 1; i++) { C[i] = A[i - v[i]] + B[v[i]]; }
  return C;
}
