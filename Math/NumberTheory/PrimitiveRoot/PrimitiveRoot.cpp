constexpr ll safe_mod(ll x, ll m) {
  x %= m;
  if(x < 0) { x += m; }
  return x;
}

constexpr ll pow_mod_constexpr(ll x, ll n, int m) {
  if(m == 1) { return 0; }
  unsigned int _m = (unsigned int)(m);
  unsigned long long r = 1, y = safe_mod(x, m);
  while(n) {
    if(n & 1) { r = (r * y) % _m; }
    y = (y * y) % _m;
    n >>= 1;
  }
  return r;
}

constexpr int PrimitiveRoot(int m) {
  if(m == 2) { return 1; }
  if(m == 167772161) { return 3; }
  if(m == 469762049) { return 3; }
  if(m == 754974721) { return 11; }
  if(m == 998244353) { return 3; }
  int divs[20] = {};
  divs[0] = 2;
  int cnt = 1, x = (m - 1) / 2;
  while(x % 2 == 0) { x /= 2; }
  for(int i = 3; (ll)(i)*i <= x; i += 2) {
    if(x % i == 0) {
      divs[cnt++] = i;
      while(x % i == 0) { x /= i; }
    }
  }
  if(x > 1) { divs[cnt++] = x; }
  for(int g = 2;; g++) {
    bool ok = true;
    for(int i = 0; i < cnt; i++) {
      if(pow_mod_constexpr(g, (m - 1) / divs[i], m) == 1) {
        ok = false;
        break;
      }
    }
    if(ok) { return g; }
  }
}
