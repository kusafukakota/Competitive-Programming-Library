template<typename T> struct DualBIT {
  fenwick_tree<T> f1, f2;
  DualBIT(int N): f1(N + 1), f2(N + 1) {}
  void add(int i, T x) { add(i, i + 1, x); }
  void add(int l, int r, T x) {
    f1.add(l, x), f1.add(r, -x);
    f2.add(l, -x * (l - 1)), f2.add(r, x * (r - 1));
  }
  T sum(int i) { return f1.sum(0, i) * (i - 1) + f2.sum(0, i); }
  T sum(int l, int r) { return sum(r) - sum(l); }
  T operator[](int i) { return sum(i + 1) - sum(i); }
};
