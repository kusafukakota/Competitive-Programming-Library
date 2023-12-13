bool is_prime(ll x) {
  if(x == 2 || x == 3 || x == 5 || x == 7) { return true; }
  if(x % 2 == 0 || x % 3 == 0 || x % 5 == 0 || x % 7 == 0) { return false; }
  if(x < 121) { return x > 1; }
  ll d = (x - 1) >> __builtin_ctzll(x - 1);
  ll p = 1, m = x - 1;
  auto internal_pow = [](ll x, ll n, ll mod) {
    __uint128_t r;
    x %= mod;
    if(n == 0) {
      r = 1;
      return r;
    }
    r = 1;
    __uint128_t c = x;
    for(; n; n >>= 1, c = (c * c) % mod) {
      if(n & 1) { r = r * c % mod; }
    }
    return r;
  };
  auto ok = [&](ll a) {
    auto y = internal_pow(a, d, x);
    ll t = d;
    while(y != p && y != m && t != x - 1) {
      y = y * y % x;
      t <<= 1;
    }
    if(y != m && t % 2 == 0) { return false; }
    return true;
  };
  if(x < (1ll << 32)) {
    for(ll a : {2, 7, 61}) {
      if(!ok(a)) { return false; }
    }
  }
  else {
    for(ll a : {2, 325, 9375, 28178, 450775, 9780504, 1795265022}) {
      if(x <= a) { return true; }
      if(!ok(a)) { return false; }
    }
  }
  return true;
}
ll Rho(ll n) {
  if(n % 2 == 0) { return 2; }
  if(is_prime(n)) { return n; }
  auto f = [&](ll x) -> ll { return (__int128_t(x) * x + 1) % n; };
  ll step = 0;
  while(1) {
    ++step;
    ll x = step, y = f(x);
    while(true) {
      ll p = gcd(y - x + n, n);
      if(p == 0 || p == n) { break; }
      if(p != 1) { return p; }
      x = f(x);
      y = f(f(y));
    }
  }
}
vector<ll> PrimeFactorize(ll n) {
  if(n == 1) { return {}; }
  ll p = Rho(n);
  if(p == n) { return {p}; }
  vector<ll> left = PrimeFactorize(p), right = PrimeFactorize(n / p);
  left.insert(left.end(), right.begin(), right.end());
  ranges::sort(left);
  return left;
}
