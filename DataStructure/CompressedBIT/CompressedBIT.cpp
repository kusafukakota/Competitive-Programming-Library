template<typename S, typename T> struct CompressedBIT {
 private:
  fenwick_tree<T> f;
  vector<S> s;
  int id(S x) const { return ranges::lower_bound(s, x) - s.begin(); }

 public:
  void use(S x) { s.emplace_back(x); }
  void build() {
    ranges::sort(s);
    s.erase(unique(s.begin(), s.end()), s.end());
    f = fenwick_tree<T>(s.size());
  }
  void add(S i, T x) { f.add(id(i), x); }
  T sum(S l, S r) { return f.sum(id(l), id(r)); }
};
