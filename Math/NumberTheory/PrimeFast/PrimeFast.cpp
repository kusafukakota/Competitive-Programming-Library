using ull = unsigned long long;

bool is_prime(ull n) {
  if(n == 2) { return true; }
  if(n % 2 == 0) { return false; }
  auto internal_pow = [&](ull x, ull y) {
    ull r = 1;
    __uint128_t c = x;
    for(; y; y >>= 1, c = c * c % n) {
      if(y & 1) { r = __uint128_t(r) * c % n; }
    }
    return r;
  };
  auto MillerRabin = [&](ull a) {
    if(n <= a) { return true; }
    int e = __builtin_ctzll(n - 1);
    ull z = internal_pow(a, (n - 1) >> e);
    if(z == 1 || z == n - 1) { return true; }
    while(--e) {
      z = __uint128_t(z) * z % n;
      if(z == 1) { return false; }
      if(z == n - 1) { return true; }
    }
    return false;
  };
  if(n < 4759123141) {
    return ranges::all_of(vector<ull>{2, 7, 61}, [&](auto x) { return MillerRabin(x); });
  }
  return ranges::all_of(vector<ull>{2, 325, 9375, 28178, 450775, 9780504, 1795265022}, [&](auto x) { return MillerRabin(x); });
}

struct Montgomery {
  ull mod, R;

 public:
  Montgomery(ull n): mod(n), R(n) {
    for(int i = 0; i < 5; i++) { R *= 2 - mod * R; }
  }
  ull fma(ull a, ull b, ull c) const {
    const __uint128_t d = __uint128_t(a) * b;
    const ull e = c + mod + (d >> 64);
    const ull f = ull(d) * R;
    const ull g = (__uint128_t(f) * mod) >> 64;
    return e - g;
  }
  ull mul(ull a, ull b) const { return fma(a, b, 0); }
};

ull PollardRho(ull n) {
  if(n % 2 == 0) { return 2; }
  const Montgomery m(n);
  constexpr ull C1 = 1, C2 = 2, M = 512;
  ull Z1 = 1, Z2 = 2;
retry:
  ull z1 = Z1, z2 = Z2;
  for(unsigned k = M;; k <<= 1) {
    const ull x1 = z1 + n, x2 = z2 + n;
    for(unsigned j = 0; j < k; j += M) {
      const ull y1 = z1, y2 = z2;
      ull q1 = 1, q2 = 2;
      z1 = m.fma(z1, z1, C1), z2 = m.fma(z2, z2, C2);
      for(unsigned i = 0; i < M; i++) {
        const ull t1 = x1 - z1, t2 = x2 - z2;
        z1 = m.fma(z1, z1, C1), z2 = m.fma(z2, z2, C2);
        q1 = m.mul(q1, t1), q2 = m.mul(q2, t2);
      }
      q1 = m.mul(q1, x1 - z1), q2 = m.mul(q2, x2 - z2);
      const ull q3 = m.mul(q1, q2), g3 = gcd(n, q3);
      if(g3 == 1) { continue; }
      if(g3 != n) { return g3; }
      const ull g1 = gcd(n, q1), g2 = gcd(n, q2);
      const ull C = g1 != 1 ? C1 : C2, x = g1 != 1 ? x1 : x2;
      ull z = g1 != 1 ? y1 : y2, g = g1 != 1 ? g1 : g2;
      if(g == n) {
        do {
          z = m.fma(z, z, C);
          g = gcd(n, x - z);
        } while(g == 1);
      }
      if(g != n) { return g; }
      Z1 += 2, Z2 += 2;
      goto retry;
    }
  }
}

void internal_Factorize(ull n, vector<ull> &r) {
  if(n <= 1) { return; }
  if(is_prime(n)) {
    r.emplace_back(n);
    return;
  }
  const ull p = PollardRho(n);
  internal_Factorize(p, r);
  internal_Factorize(n / p, r);
}

vector<ull> PrimeFactorize(ull n) {
  vector<ull> r;
  internal_Factorize(n, r);
  ranges::sort(r);
  return r;
}

vector<pair<ll, ll>> Prime(ll n) {
  vector<pair<ll, ll>> r;
  for(ll i = 2; i * i <= n; i++) {
    if(n % i != 0) { continue; }
    ll e = 0;
    while(n % i == 0) { e++, n /= i; }
    r.emplace_back(i, e);
  }
  if(n != 1) { r.emplace_back(n, 1); }
  return r;
}
