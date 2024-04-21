template<typename T> struct BIT2D {
  int H, W;
  vector<vector<T>> bit;
  BIT2D(int h, int w): H(h + 1), W(w + 1) { bit.resize(H + 3, vector<T>(W + 3, T(0))); };
  BIT2D(vector<vector<T>> v): H(v.size()), W(v[0].size()) {
    bit.resize(H + 3, vector<T>(W + 3, T(0)));
    for(int i = 0; i < H; i++) {
      for(int j = 0; j < W; j++) { add(i, j, v[i][j]); }
    }
  };
  void add(int x, int y, T w) {
    if(x < 0 || y < 0 || x >= H || y >= W) { return; }
    for(int a = (++y, ++x); a <= H; a += a & -a) {
      for(int b = y; b <= W; b += b & -b) { bit[a][b] += w; }
    }
  }
  void imos_add(int x1, int y1, int x2, int y2, T w) { add(x1, y1, w), add(x1, y2, -w), add(x2, y1, -w), add(x2, y2, w); }
  void imos_add(int x, int y, T w) { imos_add(x, y, x, y, w); }
  T sum(int x, int y) {
    x--, y--;
    T r = 0;
    for(int a = (++y, ++x); a > 0; a -= a & -a) {
      for(int b = y; b > 0; b -= b & -b) { r += bit[a][b]; }
    }
    return r;
  }
  T sum(int x1, int y1, int x2, int y2) { return sum(x2, y2) - sum(x2, y1) - sum(x1, y2) + sum(x1, y1); }
  T imos_get(int x, int y) { return sum(++x, ++y); }
};
