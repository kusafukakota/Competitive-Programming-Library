#pragma once

template<typename S, auto op, auto e> struct SegTree2D {
 private:
  vector<S> seg;
  bool built;
  int id(int x, int y) const { return x * 2 * W + y; }
  S inner_prod(int x, int ly, int ry) {
    S res = e();
    for(; ly < ry; ly >>= 1, ry >>= 1) {
      if(ly & 1) { res = op(res, seg[id(x, ly)]), ly++; }
      if(ry & 1) { --ry, res = op(res, seg[id(x, ry)]); }
    }
    return res;
  }

 public:
  int H, W;
  SegTree2D(int x, int y): built(false) {
    H = W = 1;
    while(H < x) { H <<= 1; }
    while(W < y) { W <<= 1; }
    seg.assign(4 * H * W, e());
  }
  void set(int x, int y, const S &s) {
    if(!built) { seg[id(x + H, y + W)] = s; }
    else {
      x += H, y += W;
      seg[id(x, y)] = s;
      for(int i = x >> 1; i; i >>= 1) { seg[id(i, y)] = op(seg[id(2 * i, y)], seg[id(2 * i + 1, y)]); }
      for(; x; x >>= 1) {
        for(int j = y >> 1; j; j >>= 1) { seg[id(x, j)] = op(seg[id(x, 2 * j)], seg[id(x, 2 * j + 1)]); }
      }
    }
  }
  void build() {
    built = true;
    for(int y = W; y < 2 * W; y++) {
      for(int x = H - 1; x; x--) { seg[id(x, y)] = op(seg[id(2 * x, y)], seg[id(2 * x + 1, y)]); }
    }
    for(int x = 0; x < 2 * H; x++) {
      for(int y = W - 1; y; y--) { seg[id(x, y)] = op(seg[id(x, 2 * y)], seg[id(x, 2 * y + 1)]); }
    }
  }
  S get(int x, int y) const { return seg[id(x + H, y + W)]; }
  S operator()(int x, int y) const { return seg[id(x + H, y + W)]; }
  S prod(int lx, int rx, int ly, int ry) {
    if(lx >= rx || ly >= ry) { return e(); }
    S res = e();
    lx += H, rx += H, ly += W, ry += W;
    for(; lx < rx; lx >>= 1, rx >>= 1) {
      if(lx & 1) { res = op(res, inner_prod(lx, ly, ry)), lx++; }
      if(rx & 1) { --rx, res = op(res, inner_prod(rx, ly, ry)); }
    }
    return res;
  }
  S operator()(int lx, int rx, int ly, int ry) { return prod(lx, rx, ly, ry); }
};