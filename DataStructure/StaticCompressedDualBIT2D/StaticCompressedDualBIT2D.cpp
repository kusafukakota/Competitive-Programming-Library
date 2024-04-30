namespace std {
template<typename T> tuple<T, T, T, T> operator+=(tuple<T, T, T, T> &l, tuple<T, T, T, T> r) {
  return l = make_tuple(get<0>(l) + get<0>(r), get<1>(l) + get<1>(r), get<2>(l) + get<2>(r), get<3>(l) + get<3>(r));
}
template<typename T> tuple<T, T, T, T> operator-(tuple<T, T, T, T> l, tuple<T, T, T, T> r) {
  return make_tuple(get<0>(l) - get<0>(r), get<1>(l) - get<1>(r), get<2>(l) - get<2>(r), get<3>(l) - get<3>(r));
}
}  // namespace std

template<typename S, typename T> struct StaticCompressedDualBIT2D {
 private:
  struct BIT {
   private:
    using U = tuple<T, T, T, T>;
    int n;
    vector<U> data;

   public:
    explicit BIT(int n): n(n), data(n) {}
    void add(int p, U x) {
      for(++p; p <= n; p += p & -p) { data[p - 1] += U(x); }
    }
    U sum(int r) {
      U s = {0, 0, 0, 0};
      for(; r > 0; r -= r & -r) { s += data[r - 1]; }
      return s;
    }
  };
  struct Add {
    S lx, rx, ly, ry;
    T w;
  };
  struct Sum {
    S lx, rx, ly, ry;
  };
  vector<Add> Add;
  vector<Sum> Sum;

 public:
  StaticCompressedDualBIT2D() = default;
  StaticCompressedDualBIT2D(int N, int Q) {
    Add.reserve(N);
    Sum.reserve(Q);
  }
  void add(S lx, S rx, S ly, S ry, T w) { Add.emplace_back(lx, rx, ly, ry, w); }
  void sum(S lx, S rx, S ly, S ry) { Sum.emplace_back(lx, rx, ly, ry); }
  vector<T> solve() {
    vector<S> ys;
    vector<tuple<S, S, T>> add;
    for(const auto &[lx, rx, ly, ry, w] : Add) {
      ys.emplace_back(ly);
      ys.emplace_back(ry);
      add.emplace_back(lx, ly, w);
      add.emplace_back(rx, ly, -w);
      add.emplace_back(lx, ry, -w);
      add.emplace_back(rx, ry, w);
    }
    ranges::sort(ys);
    ys.erase(unique(ys.begin(), ys.end()), ys.end());
    auto id = [&ys](S y) -> int { return ranges::lower_bound(ys, y) - ys.begin(); };
    vector<tuple<S, S, int, bool>> sum;
    for(int i = 0; i < (int)Sum.size(); i++) {
      const auto &[lx, rx, ly, ry] = Sum[i];
      sum.emplace_back(lx, ly, i, true);
      sum.emplace_back(rx, ly, i, false);
      sum.emplace_back(lx, ry, i, false);
      sum.emplace_back(rx, ry, i, true);
    }
    static constexpr auto comp = [](const auto &q1, const auto &q2) { return get<0>(q1) < get<0>(q2); };
    ranges::sort(add, comp);
    ranges::sort(sum, comp);
    BIT f(ys.size());
    vector<T> ans(Sum.size(), T{0});
    const int N = add.size(), M = sum.size();
    for(int i = 0, j = 0; i < N || j < M;) {
      if(j == M || (i < N && get<0>(add[i]) < get<0>(sum[j]))) {
        const auto [lx, ly, w] = add[i++];
        f.add(id(ly), make_tuple(w, -w * ly, -w * lx, w * lx * ly));
      }
      else {
        const auto &[x, y, qid, plus] = sum[j++];
        auto [a, b, c, d] = f.sum(id(y));
        const T tmp = a * x * y + b * x + c * y + d;
        ans[qid] += (plus ? tmp : -tmp);
      }
    }
    return ans;
  }
};
