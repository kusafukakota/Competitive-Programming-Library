#pragma once

#include <lib/FormalPowerSeries.hpp>

mint BostanMori(FPS p, FPS q, ll n) {
  ll m = max(p.size(), q.size());
  p.resize(m);
  q.resize(m);
  while(n) {
    FPS r = q;
    for(ll i = 0; i < ssize(r); i += 2) { r[i] = -r[i]; }
    FPS v = q * r, u = p * r;
    for(ll i = n % 2; i < ssize(u); i += 2) { p[i / 2] = u[i]; }
    for(ll i = 0; i < ssize(v); i += 2) { q[i / 2] = v[i]; }
    n /= 2;
  }
  return p[0] / q[0];
}

// ini = { a_0, a_1, ..., a_{k-1} }
// a_n = rec_0 * a_{n-1} + rec_1 * a_{n-2} +...+ rec_{k-1} * a_{n-k}
template<typename T, typename U> mint LinearRecurrence(const vector<T> &ini, const vector<U> &rec, ll n) {
  ll s = ini.size(), k = rec.size();
  assert(s >= k);
  FPS p, q(k + 1), a(s);
  q[0] = 1;
  for(ll i = 0; i < k; i++) { q[i + 1] = -rec[i]; }
  for(ll i = 0; i < s; i++) { a[i] = ini[i]; }
  p = (q * a).pre(k);
  return BostanMori(p, q, n);
}