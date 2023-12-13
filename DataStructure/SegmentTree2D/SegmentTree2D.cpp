template<typename S, auto op, auto e> struct SegTree2D {
  static_assert(std::is_convertible_v<decltype(op), std::function<S(S, S)>>);
  static_assert(std::is_convertible_v<decltype(e), std::function<S()>>);

 private:
  vector<S> seg;
  bool built;
  int id(int h, int w) const { return h * 2 * W + w; }
  S inner_prod(int h, int w1, int w2) {
    S res = e();
    for(; w1 < w2; w1 >>= 1, w2 >>= 1) {
      if(w1 & 1) { res = op(res, seg[id(h, w1)]), w1++; }
      if(w2 & 1) { --w2, res = op(res, seg[id(h, w2)]); }
    }
    return res;
  }

 public:
  int H, W;
  SegTree2D(int h, int w): built(false) {
    H = W = 1;
    while(H < h) { H <<= 1; }
    while(W < w) { W <<= 1; }
    seg.assign(4 * H * W, e());
  }
  void set(int h, int w, const S &x) {
    if(!built) { seg[id(h + H, w + W)] = x; }
    else {
      h += H, w += W;
      seg[id(h, w)] = x;
      for(int i = h >> 1; i; i >>= 1) { seg[id(i, w)] = op(seg[id(2 * i + 0, w)], seg[id(2 * i + 1, w)]); }
      for(; h; h >>= 1) {
        for(int j = w >> 1; j; j >>= 1) { seg[id(h, j)] = op(seg[id(h, 2 * j + 0)], seg[id(h, 2 * j + 1)]); }
      }
    }
  }
  void build() {
    built = true;
    for(int w = W; w < 2 * W; w++) {
      for(int h = H - 1; h; h--) { seg[id(h, w)] = op(seg[id(2 * h + 0, w)], seg[id(2 * h + 1, w)]); }
    }
    for(int h = 0; h < 2 * H; h++) {
      for(int w = W - 1; w; w--) { seg[id(h, w)] = op(seg[id(h, 2 * w + 0)], seg[id(h, 2 * w + 1)]); }
    }
  }
  S get(int h, int w) const { return seg[id(h + H, w + W)]; }
  S operator()(int h, int w) const { return seg[id(h + H, w + W)]; }
  S prod(int h1, int w1, int h2, int w2) {
    if(h1 >= h2 || w1 >= w2) { return e(); }
    S res = e();
    h1 += H, h2 += H, w1 += W, w2 += W;
    for(; h1 < h2; h1 >>= 1, h2 >>= 1) {
      if(h1 & 1) { res = op(res, inner_prod(h1, w1, w2)), h1++; }
      if(h2 & 1) { --h2, res = op(res, inner_prod(h2, w1, w2)); }
    }
    return res;
  }
  S operator()(int h1, int w1, int h2, int w2) { return prod(h1, w1, h2, w2); }
};
