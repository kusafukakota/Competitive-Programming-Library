template<class S, auto op, auto e, class F, auto mapping, auto composition, auto id> struct lazy_segtree {
 public:
  lazy_segtree(): lazy_segtree(0) {}
  explicit lazy_segtree(int n): lazy_segtree(vector<S>(n, e())) {}
  explicit lazy_segtree(const vector<S> &v): _n(int(v.size())) {
    size = (int)bit_ceil((unsigned int)(_n));
    log = countr_zero((unsigned int)size);
    d = vector<S>(2 * size, e());
    lz = vector<F>(size, id());
    for(int i = 0; i < _n; i++) { d[size + i] = v[i]; }
    for(int i = size - 1; i >= 1; i--) { update(i); }
  }
  void set(int p, S x) {
    assert(0 <= p && p < _n);
    p += size;
    for(int i = log; i >= 1; i--) { push(p >> i); }
    d[p] = x;
    for(int i = 1; i <= log; i++) { update(p >> i); }
  }
  S get(int p) {
    assert(0 <= p && p < _n);
    p += size;
    for(int i = log; i >= 1; i--) { push(p >> i); }
    return d[p];
  }
  S prod(int l, int r) {
    assert(0 <= l && l <= r && r <= _n);
    if(l == r) { return e(); }
    l += size;
    r += size;
    for(int i = log; i >= 1; i--) {
      if(((l >> i) << i) != l) { push(l >> i); }
      if(((r >> i) << i) != r) { push((r - 1) >> i); }
    }
    S sml = e(), smr = e();
    while(l < r) {
      if(l & 1) { sml = op(sml, d[l++]); }
      if(r & 1) { smr = op(d[--r], smr); }
      l >>= 1;
      r >>= 1;
    }
    return op(sml, smr);
  }
  S all_prod() { return d[1]; }
  void apply(int p, F f) {
    assert(0 <= p && p < _n);
    p += size;
    for(int i = log; i >= 1; i--) { push(p >> i); }
    d[p] = mapping(f, d[p]);
    for(int i = 1; i <= log; i++) { update(p >> i); }
  }
  void apply(int l, int r, F f) {
    assert(0 <= l && l <= r && r <= _n);
    if(l == r) return;
    l += size;
    r += size;
    for(int i = log; i >= 1; i--) {
      if(((l >> i) << i) != l) { push(l >> i); }
      if(((r >> i) << i) != r) { push((r - 1) >> i); }
    }
    {
      int l2 = l, r2 = r;
      while(l < r) {
        if(l & 1) { all_apply(l++, f); }
        if(r & 1) { all_apply(--r, f); }
        l >>= 1;
        r >>= 1;
      }
      l = l2;
      r = r2;
    }
    for(int i = 1; i <= log; i++) {
      if(((l >> i) << i) != l) { update(l >> i); }
      if(((r >> i) << i) != r) { update((r - 1) >> i); }
    }
  }
  template<bool (*g)(S)> int max_right(int l) {
    return max_right(l, [](S x) { return g(x); });
  }
  template<class G> int max_right(int l, G g) {
    assert(0 <= l && l <= _n);
    assert(g(e()));
    if(l == _n) { return _n; }
    l += size;
    for(int i = log; i >= 1; i--) { push(l >> i); }
    S sm = e();
    do {
      while(l % 2 == 0) l >>= 1;
      if(!g(op(sm, d[l]))) {
        while(l < size) {
          push(l);
          l = (2 * l);
          if(g(op(sm, d[l]))) {
            sm = op(sm, d[l]);
            l++;
          }
        }
        return l - size;
      }
      sm = op(sm, d[l]);
      l++;
    } while((l & -l) != l);
    return _n;
  }
  template<bool (*g)(S)> int min_left(int r) {
    return min_left(r, [](S x) { return g(x); });
  }
  template<class G> int min_left(int r, G g) {
    assert(0 <= r && r <= _n);
    assert(g(e()));
    if(r == 0) { return 0; }
    r += size;
    for(int i = log; i >= 1; i--) { push((r - 1) >> i); }
    S sm = e();
    do {
      r--;
      while(r > 1 && (r % 2)) r >>= 1;
      if(!g(op(d[r], sm))) {
        while(r < size) {
          push(r);
          r = (2 * r + 1);
          if(g(op(d[r], sm))) {
            sm = op(d[r], sm);
            r--;
          }
        }
        return r + 1 - size;
      }
      sm = op(d[r], sm);
    } while((r & -r) != r);
    return 0;
  }

 private:
  int _n, size, log;
  vector<S> d;
  vector<F> lz;
  void update(int k) { d[k] = op(d[2 * k], d[2 * k + 1]); }
  void all_apply(int k, F f) {
    d[k] = mapping(f, d[k]);
    if(k < size) {
      lz[k] = composition(f, lz[k]);
      if(d[k].fail) { push(k), update(k); }
    }
  }
  void push(int k) {
    all_apply(2 * k, lz[k]);
    all_apply(2 * k + 1, lz[k]);
    lz[k] = id();
  }
};

constexpr ll INF = 2e9;
struct S {
  ll max, lcm, sz, sum;
  bool fail;
  S(): max(0), lcm(1), sz(0), sum(0), fail(false) {}
  S(ll x, ll sz = 1): max(x), lcm(x), sz(sz), sum(x * sz), fail(false) {}
};
struct F {
  ll g, upd;
  F(): g(0), upd(0) {}
  F(ll g, ll upd): g(g), upd(upd) {}
  static F gcd(ll x) noexcept { return F(x, 0); }
  static F update(ll x) noexcept { return F(0, x); }
};
S op(S l, S r) {
  if(!r.sz) { return l; }
  if(!l.sz) { return r; }
  S ret;
  ret.max = std::max(l.max, r.max);
  ret.sum = l.sum + r.sum;
  ret.lcm = min(INF, std::lcm(l.lcm, r.lcm));
  ret.sz = l.sz + r.sz;
  return ret;
}
S e() { return S(); }
S fx(F f, S x) {
  if(x.fail) { return x; }
  if(f.upd) { x = S(f.upd, x.sz); }
  if(f.g) {
    if(x.sz * x.max == x.sum) { x = S(gcd(x.max, f.g), x.sz); }
    else if(x.lcm == INF || f.g % x.lcm) { x.fail = true; }
  }
  return x;
}
F fg(F f, F g) {
  if(f.upd) { return F::update(f.upd); }
  else if(g.upd) { return F::update(gcd(f.g, g.upd)); }
  else { return F::gcd(gcd(f.g, g.g)); }
}
F id() { return F(); }
