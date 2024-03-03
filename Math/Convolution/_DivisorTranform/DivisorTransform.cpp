vector<ll> PrimeEnum(ll n) {
  vector<bool> sieve(n / 3 + 1, true);
  for(ll p = 5, d = 4, i = 1, sq = sqrt(n); p <= sq; p += d = 6 - d, i++) {
    if(!sieve[i]) { continue; }
    for(ll q = p * p / 3, r = d * p / 3 + (d * p % 3 == 2), s = 2 * p, qe = ssize(sieve); q < qe; q += r = s - r) { sieve[q] = false; }
  }
  vector<ll> ret = {2, 3};
  for(ll p = 5, d = 4, i = 1; p <= n; p += d = 6 - d, i++) {
    if(sieve[i]) { ret.emplace_back(p); }
  }
  while(!ret.empty() && ret.back() > n) { ret.pop_back(); }
  return ret;
}

struct DivisorTransform {
  template<typename T> static void ZetaTransform(vector<T> &v) {
    ll n = ssize(v) - 1;
    for(auto &p : PrimeEnum(n)) {
      for(ll i = 1; i * p <= n; i++) { v[i * p] += v[i]; }
    }
  }
  template<typename T> static void MobiusTransform(vector<T> &v) {
    ll n = ssize(v) - 1;
    for(auto &p : PrimeEnum(n)) {
      for(ll i = n / p; i > 0; i--) { v[i * p] -= v[i]; }
    }
  }
  template<typename I, typename T> static void ZetaTransform(map<I, T> &m) {
    for(auto p = m.rbegin(); p != m.rend(); p++) {
      for(auto &x : m) {
        if(p->first == x.first) { break; }
        if(p->first % x.first == 0) { p->second += x.second; }
      }
    }
  }
  template<typename I, typename T> static void MobiusTransform(map<I, T> m) {
    for(auto &x : m) {
      for(auto p = m.rbegin(); p != m.rend(); p++) {
        if(x.first == p->first) { break; }
        if(p->first % x.first == 0) { p->second -= x.second; }
      }
    }
  }
};
