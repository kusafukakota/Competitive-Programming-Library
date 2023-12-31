template<typename T> T Bostan_Mori(FPS<T> p, FPS<T> q, ll n) {
  ll m = max(p.size(), q.size());
  p.resize(m);
  q.resize(m);
  while(n) {
    FPS<T> r = q;
    for(ll i = 0; i < ssize(r); i += 2) { r[i] = -r[i]; }
    FPS<T> v = q * r, u = p * r;
    for(ll i = n % 2; i < ssize(u); i += 2) { p[i / 2] = u[i]; }
    for(ll i = 0; i < ssize(v); i += 2) { q[i / 2] = v[i]; }
    n /= 2;
  }
  return p[0] / q[0];
}

template<typename T> T Recurrence(vector<T> &ini, vector<T> &rec, ll n) {
  ll s = ini.size(), k = rec.size();
  assert(s >= k);
  FPS<T> p, q(k + 1), a(s);
  q[0] = 1;
  for(ll i = 0; i < k; i++) { q[i + 1] = -rec[i]; }
  for(ll i = 0; i < s; i++) { a[i] = ini[i]; }
  p = (q * a).pre(k);
  return Bostan_Mori(p, q, n);
}
