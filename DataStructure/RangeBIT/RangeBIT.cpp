template<typename S, typename T> struct RangeBIT {
 private:
  S N;
  vector<fenwick_tree<T>> bit;
  vector<vector<S>> ys;
  vector<pair<S, S>> ps;
  int id(S x) const {
    return ranges::lower_bound(ps, make_pair(x, S()), [](const pair<S, S> &a, const pair<S, S> &b) { return a.first < b.first; }) - ps.begin();
  }
  int id(int i, S y) const { return ranges::lower_bound(ys[i], y) - ys[i].begin(); }

 public:
  RangeBIT() = default;
  void use(S x, S y) { ps.emplace_back(x, y); }
  void build() {
    ranges::sort(ps);
    ps.erase(unique(ps.begin(), ps.end()), ps.end());
    N = ps.size();
    bit.resize(N + 1);
    ys.resize(N + 1);
    for(int i = 0; i <= N; ++i) {
      for(int j = i + 1; j <= N; j += j & -j) { ys[j].emplace_back(ps[i].second); }
      ranges::sort(ys[i]);
      ys[i].erase(unique(ys[i].begin(), ys[i].end()), ys[i].end());
      bit[i] = fenwick_tree<T>(ys[i].size() + 1);
    }
  }
  void add(S x, S y, T a) {
    int i = ranges::lower_bound(ps, make_pair(x, y)) - ps.begin();
    assert(ps[i] == make_pair(x, y));
    for(++i; i <= N; i += i & -i) { bit[i].add(id(i, y), a); }
  }
  T sum(S x, S y) {
    T r = T();
    for(int a = id(x); a; a -= a & -a) { r += bit[a].sum(0, id(a, y)); }
    return r;
  }
  T sum(S xl, S yl, S xr, S yr) {
    T r = T();
    int a = id(xl), b = id(xr);
    while(a != b) {
      if(a < b) {
        r += bit[b].sum(id(b, yl), id(b, yr));
        b -= b & -b;
      }
      else {
        r -= bit[a].sum(id(a, yl), id(a, yr));
        a -= a & -a;
      }
    }
    return r;
  }
};
