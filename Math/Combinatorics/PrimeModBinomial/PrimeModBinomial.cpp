struct Bimomial {
 private:
  void extend(int m) {
    int n = fac.size();
    m = min(m, mint::mod() - 1);
    if(n > m) { return; }
    fac.resize(m + 1);
    finv.resize(m + 1);
    inv.resize(m + 1);
    for(int i = n; i <= m; i++) { fac[i] = fac[i - 1] * i; }
    finv[m] = fac[m].inv();
    for(int i = m - 1; i >= n; i--) { finv[i] = finv[i + 1] * (i + 1); }
    for(int i = n; i <= m; i++) { inv[i] = finv[i] * fac[i - 1]; }
  }

 public:
  vector<mint> fac, finv, inv;
  Bimomial(int n = 0): fac(1, 1), finv(1, 1), inv(1, 1) { extend(n); }
  mint operator()(int n) {
    extend(abs(n));
    return n >= 0 ? fac[n] : finv[-n];
  }
  mint operator[](int n) {
    extend(abs(n));
    return n >= 0 ? inv[n] : -inv[-n];
  }
  mint C(int n, int k) {
    if(n < 0 || k < 0 || n < k) { return 0; }
    extend(n);
    return fac[n] * finv[n - k] * finv[k];
  }
  inline mint operator()(int n, int k) { return C(n, k); }
  mint C_(ll n, ll k) {
    if(n < 0 || k < 0 || n < k) { return 0; }
    k = min(k, n - k);
    extend(k);
    mint r = 1;
    for(ll i = 0; i < k; i++) { r *= n - i; }
    return r * finv[k];
  }
  mint P(int n, int k) {
    if(n < 0 || k < 0 || n < k) { return 0; }
    extend(n);
    return fac[n] * finv[n - k];
  }
  mint P_(ll n, ll k) {
    if(n < 0 || k < 0 || n < k) { return 0; }
    k = min(k, n - k);
    mint r = 1;
    for(ll i = 0; i < k; i++) { r *= n - i; }
    return r;
  }
  mint H(int n, int k) {
    if(n < 0 || k < 0) { return 0; }
    if(n == 0 && k == 0) { return 1; }
    return C(n + k - 1, k);
  }
  mint multi(const vector<ll> &v) {
    int n = 0;
    for(auto &i : v) {
      if(i < 0) { return 0; }
      n += i;
    }
    extend(n);
    mint r = fac[n];
    for(auto &i : v) { r *= finv[i]; }
    return r;
  }
  mint operator()(const vector<ll> &v) { return multi(v); }
  mint Catalan(int n) {
    if(n < 0) { return 0; }
    extend(n * 2);
    return fac[n * 2] * finv[n] * finv[n + 1];
  }
  mint Bell(int n, int k) {
    if(n < 0 || k < 0) { return 0; }
    if(n == 0) { return 1; }
    k = min(n, k);
    extend(k);
    mint r = 0;
    vector<mint> v(k + 1);
    v[0] = 1;
    for(ll i = 1; i <= k; i++) { v[i] = v[i - 1] + (i & 1 ? -finv[i] : finv[i]); }
    for(ll i = 1; i <= k; i++) { r += (mint(i).pow(n)) * finv[i] * v[k - i]; }
    return r;
  }
  mint Stirling(ll n, ll k) {
    if(n < 0 || k < 0 || n < k) { return 0; }
    mint r = 0;
    for(ll i = 0; i <= k; i++) {
      mint t = C(k, i) * (mint(i).pow(n));
      r += (k - i) & 1 ? -t : t;
    }
    return r * finv[k];
  }
};
