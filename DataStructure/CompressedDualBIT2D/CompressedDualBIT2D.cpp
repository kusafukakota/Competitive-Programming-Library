namespace std {
template<typename T> tuple<T, T, T, T> operator+=(tuple<T, T, T, T> &l, tuple<T, T, T, T> r) {
  return l = make_tuple(get<0>(l) + get<0>(r), get<1>(l) + get<1>(r), get<2>(l) + get<2>(r), get<3>(l) + get<3>(r));
}
template<typename T> tuple<T, T, T, T> operator-(tuple<T, T, T, T> l, tuple<T, T, T, T> r) {
  return make_tuple(get<0>(l) - get<0>(r), get<1>(l) - get<1>(r), get<2>(l) - get<2>(r), get<3>(l) - get<3>(r));
}
template<typename T> tuple<T, T, T, T> operator-=(tuple<T, T, T, T> &l, tuple<T, T, T, T> r) {
  return l = l - r;
}
}  // namespace std

template<typename S, typename T> struct CompressedBIT2D {
 private:
  struct BIT {
   private:
    int n;
    vector<T> data;
    T sum(int r) {
      T s = {0, 0, 0, 0};
      for(; r > 0; r -= r & -r) { s += data[r - 1]; }
      return s;
    }

   public:
    BIT() = default;
    explicit BIT(int n): n(n), data(n) {}
    void add(int p, T x) {
      for(++p; p <= n; p += p & -p) { data[p - 1] += T(x); }
    }
    T sum(int l, int r) { return sum(r) - sum(l); }
  };
  int N;
  vector<BIT> bit;
  vector<vector<S>> ys;
  vector<pair<S, S>> ps;
  int id(S x) const {
    return ranges::lower_bound(ps, make_pair(x, S()), [](const pair<S, S> &a, const pair<S, S> &b) { return a.first < b.first; }) - ps.begin();
  }
  int id(int i, S y) const { return ranges::lower_bound(ys[i], y) - ys[i].begin(); }

 public:
  CompressedBIT2D() = default;
  CompressedBIT2D(int N) { ps.reserve(N); }
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
      bit[i] = BIT(ys[i].size() + 1);
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
  T sum(S lx, S rx, S ly, S ry) {
    T r = T();
    int a = id(lx), b = id(rx);
    while(a != b) {
      if(a < b) {
        r += bit[b].sum(id(b, ly), id(b, ry));
        b -= b & -b;
      }
      else {
        r -= bit[a].sum(id(a, ly), id(a, ry));
        a -= a & -a;
      }
    }
    return r;
  }
};

template<typename S, typename T> struct CompressedDualBIT2D {
 private:
  CompressedBIT2D<S, tuple<T, T, T, T>> B;
  static constexpr S inf = numeric_limits<S>::max();
  void add(S lx, S ly, const T &w) {
    B.add(lx, ly, make_tuple(w, -w * ly, -w * lx, w * lx * ly));
  }
  T sum(S x, S y) {
    auto [a, b, c, d] = B.sum(-inf, x, -inf, y);
    return a * x * y + b * x + c * y + d;
  }

 public:
  CompressedDualBIT2D() = default;
  void use(S lx, S rx, S ly, S ry) {
    B.use(lx, ly), B.use(rx, ly);
    B.use(lx, ry), B.use(rx, ry);
  }
  void build() { B.build(); }
  void add(S lx, S rx, S ly, S ry, const T &val) {
    add(lx, ly, val), add(rx, ly, -val);
    add(lx, ry, -val), add(rx, ry, val);
  }
  T sum(S lx, S rx, S ly, S ry) { return sum(rx, ry) - sum(rx, ly) - sum(lx, ry) + sum(lx, ly); }
};
