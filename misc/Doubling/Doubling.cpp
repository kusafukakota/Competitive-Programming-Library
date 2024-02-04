template<typename S, auto op> struct Doubling {
  static_assert(is_convertible_v<decltype(op), function<S(S, S)>>);

 private:
  int n = 0;
  vector<vector<ll>> nxts;
  vector<vector<S>> prds;

  void build() {
    vector<ll> nxt(n);
    vector<S> prd(n);
    for(int i = 0; i < n; i++) {
      if(int j = nxts.back()[i]; in(j)) {
        nxt[i] = nxts.back()[j];
        prd[i] = op(prds.back()[i], prds.back()[j]);
      }
      else {
        nxt[i] = j;
        prd[i] = prds.back()[i];
      }
    }
    nxts.emplace_back(move(nxt));
    prds.emplace_back(move(prd));
  }
  inline bool in(int i) const noexcept { return 0 <= i && i < n; }
  int pow_next(int s, int d) {
    assert(in(s));
    while(ssize(nxts) <= d) { build(); }
    return nxts[d][s];
  }
  const S &pow_prod(int s, int d) {
    assert(in(s));
    while(ssize(nxts) <= d) { build(); }
    return prds[d][s];
  }

 public:
  Doubling() = default;
  Doubling(const vector<ll> &g, vector<S> &w): n(ssize(g)), nxts(1, g), prds(1, w) { assert(ssize(g) == ssize(w)); }
  int next(int s, ll k) {
    for(int d = 0; k > 0 && in(s); d++, k >>= 1) {
      if(k & 1) { s = pow_next(s, d); }
    }
    return s;
  }
  S prod(int s, ll len) {
    assert(in(s));
    assert(len > 0);
    int d = 0;
    while(!(len & 1)) {
      d++;
      len /= 2;
    }
    S r = pow_prod(s, d);
    s = pow_next(s, d);
    for(++d, len /= 2; len && in(s); d++, len /= 2) {
      if(len & 1) {
        r = op(r, pow_prod(s, d));
        s = pow_next(s, d);
      }
    }
    return r;
  }
  int distance(int s, int l, int r) {
    assert(in(s));
    if(s <= l || r <= s) { return 0; }
    int d = 0;
    while(l < pow_next(s, d) && pow_next(s, d) < r) {
      if((1 << d) >= n) { return -1; }
      d++;
    }
    int ret = 0, cur = s;
    for(--d; d >= 0; d--) {
      if(int nxt = pow_next(cur, d); l < nxt && nxt < r) {
        ret += 1 << d;
        cur = nxt;
      }
    }
    return ret + 1;
  }
  template<typename F> ll maxlen(const int s, F f, const int maxd = 60) {
    assert(in(s));
    int d = 0;
    while(d <= maxd && f(pow_prod(s, d))) {
      if(!in(pow_next(s, d))) { return 1LL << maxd; }
      d++;
    }
    if(d > maxd) { return 1LL << maxd; }
    d--;
    int cur = pow_next(s, d);
    ll len = 1LL << d;
    S p = pow_prod(s, d);
    for(int e = d - 1; e >= 0; e--) {
      if(S nxtp = op(p, pow_prod(cur, e)); f(nxtp)) {
        swap(p, nxtp);
        cur = pow_next(cur, e);
        len += 1LL << e;
      }
    }
    return len;
  }
};
