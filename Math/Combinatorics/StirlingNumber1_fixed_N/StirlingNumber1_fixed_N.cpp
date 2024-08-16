FPS<> TaylorShift(FPS<> f, mint c) {
  const int N = f.size();
  for(int i = 0; i < N; i++) { f[i] *= C(i); }
  f = f.rev();
  FPS<> g(N, 1);
  for(int i = 1; i < N; i++) { g[i] = g[i - 1] * c * C[i]; }
  f = (f * g).pre(N);
  f = f.rev();
  for(int i = 0; i < N; i++) { f[i] *= C(-i); }
  return f;
}

FPS<> Stirling1(int N) {
  if(N <= 0) { return {1}; }
  int lg = 31 - __builtin_clz(N);
  FPS<> f{0, 1};
  for(int i = lg - 1; i >= 0; i--) {
    int n = N >> i;
    f *= TaylorShift(f, mint(n >> 1));
    if(n & 1) { f = (f << 1) + f * (n - 1); }
  }
  return f;
}
