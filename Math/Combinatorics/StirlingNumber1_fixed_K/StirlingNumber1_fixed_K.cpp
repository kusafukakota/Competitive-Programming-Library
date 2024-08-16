FPS<> Stirling1(int K, int N) {  // fixed K
  if(N < K) { return {}; }
  FPS<> f(N + 1);
  for(int i = 1; i <= N; i++) { f[i] = C[i]; }
  f = f.pow(K) * C(-K);
  for(int i = K; i <= N; i++) { f[i] *= C(i); }
  return f;
}
