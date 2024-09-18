vector<int> PrimeEnum(ll n) {
  vector<bool> sieve(n / 3 + 1, true);
  for(ll p = 5, d = 4, i = 1, sq = sqrt(n); p <= sq; p += d = 6 - d, i++) {
    if(!sieve[i]) { continue; }
    for(ll q = p * p / 3, r = d * p / 3 + (d * p % 3 == 2), s = 2 * p, qe = ssize(sieve); q < qe; q += r = s - r) { sieve[q] = false; }
  }
  vector<int> ret = {2, 3};
  for(ll p = 5, d = 4, i = 1; p <= n; p += d = 6 - d, i++) {
    if(sieve[i]) { ret.emplace_back(p); }
  }
  while(!ret.empty() && ret.back() > n) { ret.pop_back(); }
  return ret;
}

template<typename T, auto f> struct MultiplicativeFunctionPrefixSum {
 private:
  ll M, sq, s;
  int ps;
  T ans;
  vector<int> p;
  vector<T> buf;
  void dfs(int i, int c, ll prod, T cur) {
    ans += cur * f(p[i], c + 1);
    ll lim = quo(M, prod);
    if(lim >= 1LL * p[i] * p[i]) { dfs(i, c + 1, p[i] * prod, cur); }
    cur *= f(p[i], c);
    ans += cur * (buf[idx(lim)] - buf[idx(p[i])]);
    int j = i + 1;
    for(; j < ps && p[j] < (1 << 21) && 1LL * p[j] * p[j] * p[j] <= lim; j++) { dfs(j, 1, prod * p[j], cur); }
    for(; j < ps && 1LL * p[j] * p[j] <= lim; j++) {
      T sm = f(p[j], 2);
      int id1 = idx(quo(lim, p[j])), id2 = idx(p[j]);
      sm += f(p[j], 1) * (buf[id1] - buf[id2]);
      ans += cur * sm;
    }
  }
  ll quo(ll n, ll d) { return double(n) / d; }
  ll idx(ll n) { return n <= sq ? s - n : quo(M, n); }

 public:
  MultiplicativeFunctionPrefixSum(ll m): M(m) {
    assert(m <= 1e15);
    sq = sqrt(M);
    while(sq * sq > M) { sq--; }
    while((sq + 1) * (sq + 1) <= M) { sq++; }
    if(M) {
      ll hls = quo(M, sq);
      while(hls != 1 && quo(M, hls - 1) == sq) { hls--; }
      s = hls + sq;
      p = PrimeEnum(sq);
      ps = p.size();
      ans = T{};
    }
  }
  // [i] : M / i 以下の素数の個数
  vector<T> prime() {
    if(!M) { return {}; }
    ll hls = s - sq;
    vector<ll> hl(hls);
    for(int i = 1; i < hls; i++) { hl[i] = quo(M, i) - 1; }
    vector<int> hs(sq + 1);
    iota(hs.begin(), hs.end(), -1);
    int pi = 0;
    for(auto &x : p) {
      ll x2 = ll(x) * x, imax = min<ll>(hls, quo(M, x2) + 1);
      for(ll i = 1, ix = x; i < imax; ++i, ix += x) { hl[i] -= (ix < hls ? hl[ix] : hs[quo(M, ix)]) - pi; }
      for(int n = sq; n >= x2; n--) { hs[n] -= hs[quo(n, x)] - pi; }
      pi++;
    }
    vector<T> res;
    res.reserve(2 * sq + 10);
    for(auto &i : hl) { res.push_back(i); }
    for(int i = hs.size(); --i;) { res.push_back(hs[i]); }
    assert((int)res.size() == s);
    return res;
  }
  // [r][i] : m で割った余りが r で M / i 以下の素数の個数
  vector<vector<T>> prime(ll m) {
    if(m == 1) { return {prime()}; }
    ll hls = s - sq;
    vector<vector<ll>> hl(m, vector<ll>(hls, 0)), hs(m, vector<ll>(sq + 1, 0));
    for(int i = 1; i < hls; i++) {
      ll q = quo(M, i);
      for(int j = 0; j < m && j <= q; j++) { hl[j][i] = quo(q - j, m) + (j >= 2); }
    }
    for(int i = 0; i <= sq; i++) {
      for(int j = 0; j < m && j <= i; j++) { hs[j][i] = quo(i - j, m) + (j >= 2); }
    }
    vector<ll> pi(m, 0);
    for(auto &x : p) {
      ll x2 = ll(x) * x, imax = min<ll>(hls, quo(M, x2) + 1);
      for(ll i = 1, ix = x; i < imax; ++i, ix += x) {
        for(int j = 0; j < m; j++) { hl[j * x % m][i] -= (ix < hls ? hl[j][ix] : hs[j][quo(M, ix)]) - pi[j]; }
      }
      for(int n = sq; n >= x2; n--) {
        for(int j = 0; j < m; j++) { hs[j * x % m][n] -= hs[j][quo(n, x)] - pi[j]; }
      }
      pi[x % m]++;
    }
    vector<vector<T>> res(m);
    for(ll i = 0; i < m; i++) {
      for(auto &j : hl[i]) { res[i].push_back(j); }
      for(int j = hs[i].size(); --j;) { res[i].push_back(hs[i][j]); }
    }
    assert((int)res[0].size() == s);
    return res;
  }
  // i : M/i 以下の素数の総和
  vector<T> prime_sum() {
    if(!M) { return {}; }
    ll hls = s - sq;
    vector<T> h(s);
    T inv2 = T{2}.inv();
    for(int i = 1; i < hls; i++) {
      T x = quo(M, i);
      h[i] = x * (x + 1) * inv2 - 1;
    }
    for(int i = 1; i <= sq; i++) {
      T x = i;
      h[s - i] = x * (x + 1) * inv2 - 1;
    }
    for(auto &x : p) {
      T xt = x, pi = h[s - x + 1];
      ll x2 = ll(x) * x, imax = min<ll>(hls, quo(M, x2) + 1), ix = x;
      for(ll i = 1; i < imax; ++i, ix += x) { h[i] -= ((ix < hls ? h[ix] : h[s - quo(M, ix)]) - pi) * xt; }
      for(int n = sq; n >= x2; n--) { h[s - n] -= (h[s - quo(n, x)] - pi) * xt; }
    }
    assert((int)h.size() == s);
    return h;
  }
  // Fp destructive
  T run(const vector<T> &Fp) {
    if(!M) { return {}; }
    assert((int)Fp.size() == s);
    buf = Fp;
    ans = buf[idx(M)] + 1;
    for(int i = 0; i < ps; i++) { dfs(i, 1, p[i], 1); }
    return ans;
  }
};
