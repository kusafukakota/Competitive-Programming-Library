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

uint64_t Root(uint64_t a, int k = 2) {
  if(a <= 1 || k == 1) { return a; }
  if(k >= 64) { return 1; }
  auto check = [&](__uint128_t n) {
    __uint128_t x = 1, m = n;
    for(ll p = k; p; p >>= 1, m *= m) {
      if(p & 1) { x *= m; }
    }
    return x <= a;
  };
  uint64_t n = powl(a, (long double)(1.0) / k);
  while(!check(n)) { --n; }
  while(check(n + 1)) { ++n; }
  return n;
}

vector<vector<pair<ll, ll>>> PrimeRange(ll l, ll r) {
  int n = r - l + 1;
  vector<ll> v(n);
  iota(v.begin(), v.end(), l);
  vector<vector<pair<ll, ll>>> p(n);
  for(auto &i : PrimeEnum(Root(r))) {
    for(ll j = (l + i - 1) / i * i; j <= r; j += i) {
      int c = 0;
      while(v[j - l] % i == 0) {
        v[j - l] /= i;
        c++;
      }
      if(c) { p[j - l].emplace_back(i, c); }
    }
  }
  for(int i = 0; i < n; i++) {
    if(v[i] != 1) { p[i].emplace_back(v[i], 1); }
  }
  return p;
}
