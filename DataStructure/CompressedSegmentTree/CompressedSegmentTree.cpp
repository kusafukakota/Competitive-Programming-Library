template<typename T, typename S, auto op, auto e> struct CompressedSegTree {
 private:
  segtree<S, op, e> seg;
  vector<T> p;
  int id(T x) { return ranges::lower_bound(p, x) - p.begin(); }

 public:
  CompressedSegTree() = default;
  CompressedSegTree(int N) { p.reserve(N); }
  void use(ll x) { p.emplace_back(x); }
  void build() {
    ranges::sort(p);
    p.erase(unique(p.begin(), p.end()), p.end());
    seg = segtree<S, op, e>(p.size());
  }
  void set(T i, S x) { seg.set(id(i), x); }
  S get(T i) { return seg.get(id(i)); }
  S prod(T l, T r) { return seg.prod(id(l), id(r)); }
  S all_prod() { return seg.all_prod(); }
  template<auto f> int max_right(T l) {
    return seg.max_right(id(l), [](S x) { return f(x); });
  }
  template<auto f> int min_left(T r) {
    return seg.min_left(id(r), [](S x) { return f(x); });
  }
};
