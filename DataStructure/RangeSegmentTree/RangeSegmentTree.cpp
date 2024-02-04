template<typename S, typename T, auto op, auto e> struct RangeSegTree {
  static_assert(is_convertible_v<decltype(op), function<T(T, T)>>);
  static_assert(is_convertible_v<decltype(e), function<T()>>);

 private:
  S N;
  vector<segtree<T, op, e>> seg;
  vector<vector<S>> ys;
  vector<pair<S, S>> ps;
  int id(S x) const {
    return ranges::lower_bound(ps, make_pair(x, S()), [](const pair<S, S> &a, const pair<S, S> &b) { return a.first < b.first; }) - ps.begin();
  }
  int id(int i, S y) const { return ranges::lower_bound(ys[i], y) - ys[i].begin(); }

 public:
  RangeSegTree() = default;
  void use(S x, S y) { ps.emplace_back(x, y); }
  void build() {
    ranges::sort(ps);
    ps.erase(unique(ps.begin(), ps.end()), ps.end());
    N = ps.size();
    seg.resize(2 * N);
    ys.resize(2 * N);
    for(int i = 0; i < N; i++) {
      ys[i + N].emplace_back(ps[i].second);
      seg[i + N] = segtree<T, op, e>(1);
    }
    for(int i = N - 1; i; i--) {
      ys[i].resize(ys[i << 1].size() + ys[i << 1 | 1].size());
      ranges::merge(ys[i << 1], ys[i << 1 | 1], ys[i].begin());
      ys[i].erase(unique(ys[i].begin(), ys[i].end()), ys[i].end());
      seg[i] = segtree<T, op, e>(ys[i].size());
    }
  }
  void add(S x, S y, T a) {
    int i = ranges::lower_bound(ps, make_pair(x, y)) - ps.begin();
    assert(ps[i] == make_pair(x, y));
    for(i += N; i; i >>= 1) { seg[i].set(id(i, y), seg[i].get(id(i, y)) + a); }
  }
  T prod(S xl, S yl, S xr, S yr) {
    T L = e(), R = e();
    int a = id(xl), b = id(xr);
    for(a += N, b += N; a < b; a >>= 1, b >>= 1) {
      if(a & 1) {
        L = op(L, seg[a].prod(id(a, yl), id(a, yr)));
        a++;
      }
      if(b & 1) {
        b--;
        R = op(seg[b].prod(id(b, yl), id(b, yr)), R);
      }
    }
    return op(L, R);
  }
};
