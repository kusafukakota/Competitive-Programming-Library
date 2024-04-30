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
  void add(int x, int y, T a = 1) { v[x + 1][y + 1] += a; }
  void imos_add(int lx, int rx, int ly, int ry, T a = 1) { add(lx, ly, a), add(lx, ry, -a), add(rx, ly, -a), add(rx, ry, a); }
  void build() {
    for(int i = 1; i < (int)v.size(); i++) {
      for(int j = 1; j < (int)v[i].size(); j++) { v[i][j] += v[i][j - 1] + v[i - 1][j] - v[i - 1][j - 1]; }
    }
  }
  T sum(int lx, int rx, int ly, int ry) const { return v[rx][ry] - v[lx][ry] - v[rx][ly] + v[lx][ly]; }
  T operator()(int lx, int rx, int ly, int ry) const { return v[rx][ry] - v[lx][ry] - v[rx][ly] + v[lx][ly]; }
  T imos_get(int x, int y) { return v[x + 1][y + 1]; }
  vector<vector<T>> imos() const { return v; }
};
