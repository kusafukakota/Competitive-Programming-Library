#pragma once

template<typename T, typename TN, typename TN2> struct RangeLinearAddRangeMin {
  struct point {
    int x;
    T y;
    static TN cross(const point &a, const point &b, const point &c) { return (TN)(b.y - a.y) * (c.x - a.x) - (TN)(c.y - a.y) * (b.x - a.x); }
  };
  struct node {
    point lbr, rbr;
    T lza, lzb;
    node(int x, T y): lbr{x, y}, rbr{x, y}, lza(0), lzb(0) {}
    node(): lza(0), lzb(0) {}
  };

 private:
  int _n, size, log;
  vector<node> nd;
  void all_apply(int k, T a, T b) {
    nd[k].lbr.y += a * nd[k].lbr.x + b;
    nd[k].rbr.y += a * nd[k].rbr.x + b;
    if(k < size) { nd[k].lza += a, nd[k].lzb += b; }
  }
  void push(int k) {
    all_apply(2 * k, nd[k].lza, nd[k].lzb);
    all_apply(2 * k + 1, nd[k].lza, nd[k].lzb);
    nd[k].lza = nd[k].lzb = 0;
  }
  int leftmost(int k) {
    int msb = 31 - __builtin_clz(k);
    return (k - (1 << msb)) << (log - msb);
  }
  void pull(int k) {
    assert(k < size);
    int l = k * 2, r = k * 2 + 1;
    int splitx = leftmost(r);
    push(k);
    T lza = 0, lzb = 0, lzA = 0, lzB = 0;
    point a = nd[l].lbr, b = nd[l].rbr, c = nd[r].lbr, d = nd[r].rbr;
    auto movel = [&](int f) {
      lza += nd[l].lza, lzb += nd[l].lzb;
      l = l * 2 + f;
      a = nd[l].lbr, b = nd[l].rbr;
      a.y += lza * a.x + lzb;
      b.y += lza * b.x + lzb;
    };
    auto mover = [&](int f) {
      lzA += nd[r].lza, lzB += nd[r].lzb;
      r = r * 2 + f;
      c = nd[r].lbr, d = nd[r].rbr;
      c.y += lzA * c.x + lzB;
      d.y += lzA * d.x + lzB;
    };
    while(l < size || r < size) {
      TN2 s1 = point::cross(a, b, c);
      if(l < size && s1 > 0) { movel(0); }
      else if(r < size && point::cross(b, c, d) > 0) { mover(1); }
      else if(l >= size) { mover(0); }
      else if(r >= size) { movel(1); }
      else {
        TN2 s2 = point::cross(b, a, d);
        assert(s1 + s2 >= 0);
        if(s1 + s2 == 0 || s1 * (d.x - splitx) < s2 * (splitx - c.x)) { movel(1); }
        else { mover(0); }
      }
    }
    nd[k].lbr = a;
    nd[k].rbr = c;
  }
  T min_subtree(int k) {
    T a = 0, b = 0;
    while(k < size) {
      bool f = (nd[k].lbr.y - nd[k].rbr.y) > a * (nd[k].rbr.x - nd[k].lbr.x);
      a += nd[k].lza;
      b += nd[k].lzb;
      k = k * 2 + f;
    }
    return nd[k].lbr.y + a * nd[k].lbr.x + b;
  }

 public:
  static constexpr T inf = numeric_limits<T>::max();
  RangeLinearAddRangeMin(): RangeLinearAddRangeMin(0) {}
  explicit RangeLinearAddRangeMin(int n): RangeLinearAddRangeMin(vector<T>(n, 0)) {}
  explicit RangeLinearAddRangeMin(const vector<T> &v): _n(int(v.size())) {
    size = (int)bit_ceil((unsigned int)(_n));
    log = countr_zero((unsigned int)size);
    nd = vector<node>(2 * size);
    for(int i = 0; i < size; i++) { nd[size + i] = node(i, (i < _n ? v[i] : 0)); }
    for(int i = size - 1; i >= 1; i--) { pull(i); }
  }
  T prod(int l, int r) {
    assert(0 <= l && l <= r && r <= _n);
    if(l == r) { return inf; }
    l += size;
    r += size;
    for(int i = log; i >= 1; i--) {
      if(((l >> i) << i) != l) { push(l >> i); }
      if(((r >> i) << i) != r) { push((r - 1) >> i); }
    }
    T res = inf;
    while(l < r) {
      if(l & 1) { res = min(res, min_subtree(l++)); }
      if(r & 1) { res = min(res, min_subtree(--r)); }
      l >>= 1;
      r >>= 1;
    }
    return res;
  }
  void apply(int l, int r, T a, T b) {
    assert(0 <= l && l <= r && r <= _n);
    if(l == r) { return; }
    l += size;
    r += size;
    {
      int l2 = l, r2 = r;
      while(l < r) {
        if(l & 1) { all_apply(l++, a, b); }
        if(r & 1) { all_apply(--r, a, b); }
        l >>= 1;
        r >>= 1;
      }
      l = l2;
      r = r2;
    }
    for(int i = 1; i <= log; i++) {
      if(((l >> i) << i) != l) { pull(l >> i); }
      if(((r >> i) << i) != r) { pull((r - 1) >> i); }
    }
  }
};