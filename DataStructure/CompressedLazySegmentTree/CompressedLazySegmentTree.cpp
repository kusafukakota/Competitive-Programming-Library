template<typename T, typename S, auto op, auto e, typename F, auto fx, auto fg, auto id> struct CompressedLazySegTree {
 private:
  lazy_segtree<S, op, e, F, fx, fg, id> seg;
  vector<T> p;
  int idx(T x) { return ranges::lower_bound(p, x) - p.begin(); }

 public:
  CompressedLazySegTree() = default;
  CompressedLazySegTree(int N) { p.reserve(N); }
  void use(T x) { p.emplace_back(x); }
  void build() {
    ranges::sort(p);
    p.erase(unique(p.begin(), p.end()), p.end());
    seg = lazy_segtree<S, op, e, F, fx, fg, id>(p.size());
  }
  void set(T i, S x) { seg.set(idx(i), x); }
  S get(T i) { return seg.get(idx(i)); }
  S prod(T l, T r) { return seg.prod(idx(l), idx(r)); }
  S all_prod() { return seg.all_prod(); }
  void apply(T i, F f) { seg.apply(idx(i), f); }
  void apply(T l, T r, F f) { seg.apply(idx(l), idx(r), f); }
  template<auto f> int max_right(T l) {
    return seg.max_right(idx(l), [](S x) { return f(x); });
  }
  template<auto f> int min_left(T r) {
    return seg.min_left(idx(r), [](S x) { return f(x); });
  }
};
