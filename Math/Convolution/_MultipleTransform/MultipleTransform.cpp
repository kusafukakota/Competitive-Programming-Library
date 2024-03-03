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

struct MultipleTransform {
  template<typename T> static void ZetaTransform(vector<T> &v) {
    const int n = v.size() - 1;
    for(auto &p : PrimeEnum(n)) {
      for(ll i = n / p; i > 0; i--) { v[i] += v[i * p]; }
    }
  }
  template<typename T> static void MobiusTransform(vector<T> &v) {
    const int n = v.size() - 1;
    for(auto &p : PrimeEnum(n)) {
      for(ll i = 1; i * p <= n; i++) { v[i] -= v[i * p]; }
    }
  }
  template<typename I, typename T> static void ZetaTransform(map<I, T> &m) {
    for(auto &x : m) {
      for(auto p = m.rbegin(); p->first != x.first; p++) {
        if(p->first % x.first == 0) { x.second += p->second; }
      }
    }
  }
  template<typename I, typename T> static void MobiusTransform(map<I, T> &m) {
    for(auto p1 = m.rbegin(); p1 != m.rend(); p1++) {
      for(auto p2 = m.rbegin(); p2 != p1; p2++) {
        if(p2->first % p1->first == 0) { p1->second -= p2.second; }
      }
    }
  }
};
