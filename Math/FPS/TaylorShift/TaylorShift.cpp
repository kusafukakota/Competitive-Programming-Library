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
