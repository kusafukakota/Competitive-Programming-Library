template<typename S, auto op, auto e> struct DualSegTree {
  vector<S> seg;
  int N, size = 1;
  DualSegTree(int n): DualSegTree(vector<S>(n, e())) {}
  DualSegTree(const vector<S> &v): N(v.size()) {
    while(size < N) { size <<= 1; }
    seg = vector<S>(size * 2, e());
    for(int i = 0; i < N; i++) { seg[size + i] = v[i]; }
  }
  void set(int i, const S &x) {
    i += size;
    for(int h = bit_width((unsigned)i); h; h--) {
      ll j = i >> h;
      if(seg[j] != e()) {
        seg[j * 2] = op(seg[j * 2], seg[j]);
        seg[j * 2 + 1] = op(seg[j * 2 + 1], seg[j]);
        seg[j] = e();
      }
    }
    seg[i] = x;
  }
  S get(int i) {
    S r = e();
    for(i += size; i; i >>= 1) { r = op(r, seg[i]); }
    return r;
  }
  void apply(int l, int r, const S &x) {
    for(l += size, r += size; l < r; l >>= 1, r >>= 1) {
      if(l & 1) { seg[l++] = op(seg[l], x); }
      if(r & 1) { seg[r] = op(seg[--r], x); }
    }
  }
};
