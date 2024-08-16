FPS<> Partition(int N) {
  FPS<> f(N + 1);
  f[0] = 1;
  for(ll i = 1; i <= N; i++) {
    ll x = i * (3 * i + 1) / 2, y = i * (3 * i - 1) / 2;
    if(y > N) { break; }
    if(x <= N) { f[x] += (i & 1 ? -1 : 1); }
    if(y <= N) { f[y] += (i & 1 ? -1 : 1); }
  }
  return f.inv();
}
