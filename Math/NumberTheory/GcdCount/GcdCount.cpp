bool is_prime(ll N) {
  if(N == 2 || N == 3 || N == 5 || N == 7) { return true; }
  if(N % 2 == 0 || N % 3 == 0 || N % 5 == 0 || N % 7 == 0) { return false; }
  if(N < 121) { return N > 1; }
  ll d = (N - 1) >> __builtin_ctzll(N - 1);
  ll p = 1, m = N - 1;
  auto internal_pow = [&](ll x, ll n) -> __uint128_t {
    __uint128_t r;
    x %= N;
    if(n == 0) { return 1; }
    r = 1;
    __uint128_t c = x;
    for(; n; n >>= 1, c = (c * c) % N) {
      if(n & 1) { r = r * c % N; }
    }
    return r;
  };
  auto ok = [&](ll a) {
    auto y = internal_pow(a, d);
    ll t = d;
    for(; y != p && y != m && t != N - 1; t <<= 1) { y = y * y % N; }
    if(y != m && t % 2 == 0) { return false; }
    return true;
  };
  if(N < (1ll << 32)) {
    for(ll a : {2, 7, 61}) {
      if(!ok(a)) { return false; }
    }
  }
  else {
    for(ll a : {2, 325, 9375, 28178, 450775, 9780504, 1795265022}) {
      if(N <= a) { return true; }
      if(!ok(a)) { return false; }
    }
  }
  return true;
}

ll Rho(ll N) {
  if(N % 2 == 0) { return 2; }
  if(is_prime(N)) { return N; }
  ll ds = [&]() -> ll {
    ll n = ll(sqrt(N));
    for(ll i = 0; i < 300; ++i) {
      ll T = (n + i) * (n + i) - N;
      ll t = ll(sqrt(T));
      if(t * t == T) { return n + i - t; }
    }
    return 0;
  }();
  if(ds > 1) { return ds; }
  auto f = [&](ll x) -> ll { return (__int128_t(x) * x + 1) % N; };
  ll st = 0;
  while(true) {
    ++st;
    ll x = st, y = f(x);
    while(true) {
      ll p = gcd(y - x + N, N);
      if(p == 0 || p == N) { break; }
      if(p != 1) { return p; }
      x = f(x);
      y = f(f(y));
    }
  }
}

vector<ll> PrimeFactorize(ll N) {
  if(N == 1) { return {}; }
  ll p = Rho(N);
  if(p == N) { return {p}; }
  vector<ll> l = PrimeFactorize(p), r = PrimeFactorize(N / p);
  l.insert(l.end(), r.begin(), r.end());
  ranges::sort(l);
  return l;
}

vector<ll> Divisor(const vector<ll> &p) {
  vector<vector<ll>> x(1, {1});
  ll num = 1, idx = 0;
  for(int i = 0; i < (int)p.size(); i++) {
    num *= p[i];
    x[idx].emplace_back(num);
    if(i != (int)p.size() - 1 && p[i + 1] != p[i]) {
      x.push_back({1});
      num = 1;
      idx++;
    }
  }
  ll l = 0, r = 1;
  vector<ll> ret{1};
  for(int i = 0; i < (int)x.size(); i++) {
    for(auto &e : x[i]) {
      for(int j = l; j < r; j++) { ret.emplace_back(ret[j] * e); }
    }
    l = r;
    r = ret.size();
  }
  return vector<ll>(ret.begin() + l, ret.end());
}

// i∈[1,n] で gcd(i, k) == first となるものの個数/総和を求める
template<bool sum = false, typename T = ll> vector<pair<ll, T>> GcdCount(ll n, ll k) {
  auto p = PrimeFactorize(k);
  auto div = Divisor(p);
  p.erase(unique(p.begin(), p.end()), p.end());
  ll s = p.size();
  vector<pair<ll, bool>> e;
  for(ll i = 0; i < 1 << s; i++) {
    ll t = 1;
    bool odd = false;
    for(ll j = 0; j < s; j++) {
      if(i & 1 << j) {
        t *= p[j];
        odd = !odd;
      }
    }
    e.emplace_back(t, odd);
  }

  vector<pair<ll, T>> ret;
  for(auto &i : div) {
    T r = 0, tmp;
    ll K = k / i, N = n / i, cnt;
    for(auto &[t, odd] : e) {
      if(K % t) { continue; }
      cnt = N / t;
      if(!sum) { tmp = cnt; }
      else { tmp = T(cnt + 1) * cnt * t * i / 2; }
      r += odd ? -tmp : tmp;
    }
    ret.emplace_back(i, r);
  }
  return ret;
}
