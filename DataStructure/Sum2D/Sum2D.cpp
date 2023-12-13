template<typename T> struct Sum2D {
  int H, W;
  vector<vector<T>> v;
  Sum2D(int h, int w): H(h), W(w), v(H + 3, vector<T>(W + 3, 0)) {}
  Sum2D(vector<vector<T>> &ini): H(ini.size()), W(ini[0].size()), v(H + 3, vector<T>(W + 3, 0)) {
    for(int i = 0; i < H; i++) {
      for(int j = 0; j < W; j++) { v[i + 1][j + 1] += ini[i][j]; }
    }
    build();
  }
  void add(int h, int w, T z = 1) { v[h + 1][w + 1] += z; }
  void imos_add(int h1, int w1, int h2, int w2, T z = 1) { add(h1, w1, z), add(h1, w2, -z), add(h2, w1, -z), add(h2, w2, z); }
  void build() {
    for(int i = 1; i < (int)v.size(); i++) {
      for(int j = 1; j < (int)v[i].size(); j++) { v[i][j] += v[i][j - 1] + v[i - 1][j] - v[i - 1][j - 1]; }
    }
  }
  T sum(int h1, int w1, int h2, int w2) const { return v[h2][w2] - v[h1][w2] - v[h2][w1] + v[h1][w1]; }
  T operator()(int h, int w) const { return v[h][w]; }
  T operator()(int h1, int w1, int h2, int w2) const { return v[h2][w2] - v[h1][w2] - v[h2][w1] + v[h1][w1]; }
  T imos_get(int h, int w) { return v[h + 1][w + 1]; }
  vector<vector<T>> imos() const { return v; }
};
