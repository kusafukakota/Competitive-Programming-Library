template<typename T, typename S, auto op, auto e, typename F, auto fx, auto fg, auto id> struct CompressedLazySegTree {
 private:
  lazy_segtree<S, op, e, F, fx, fg, id> seg;
  vector<T> s;
  int idx(T x) { return ranges::lower_bound(s, x) - s.begin(); }

 public:
  void use(T x) { s.emplace_back(x); }
  void build() {
    ranges::sort(s);
    s.erase(unique(s.begin(), s.end()), s.end());
    seg = lazy_segtree<S, op, e, F, fx, fg, id>(s.size());
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
