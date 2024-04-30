template<typename S, typename T> struct StaticCompressedDualBIT2D {
  vector<tuple<S, S, S, S, T>> Add;
  vector<tuple<S, S, S, S>> Sum;
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
      ys.emplace_back(ly), ys.emplace_back(ry);
      add.emplace_back(lx, ly, w), add.emplace_back(rx, ly, -w);
      add.emplace_back(lx, ry, -w), add.emplace_back(rx, ry, w);
    }
    ranges::sort(ys);
    ys.erase(unique(ys.begin(), ys.end()), ys.end());
    auto id = [&ys](S y) -> int { return ranges::lower_bound(ys, y) - ys.begin(); };
    vector<tuple<S, S, int, bool>> sum;
    for(int i = 0; i < (int)Sum.size(); i++) {
      const auto &[lx, rx, ly, ry] = Sum[i];
      sum.emplace_back(lx, ly, i, true), sum.emplace_back(rx, ly, i, false);
      sum.emplace_back(lx, ry, i, false), sum.emplace_back(rx, ry, i, true);
    }
    static constexpr auto comp = [](const auto &q1, const auto &q2) { return get<0>(q1) < get<0>(q2); };
    ranges::sort(add, comp);
    ranges::sort(sum, comp);
    fenwick_tree<T> f[4];
    for(int i = 0; i < 4; i++) { f[i] = fenwick_tree<T>(ys.size()); }
    vector<T> ans(Sum.size(), T{0});
    const int N = add.size(), M = sum.size();
    for(int i = 0, j = 0; i < N || j < M;) {
      if(j == M || (i < N && get<0>(add[i]) < get<0>(sum[j]))) {
        const auto [lx, ly, w] = add[i++];
        int idy = id(ly);
        f[0].add(idy, w);
        f[1].add(idy, -w * ly);
        f[2].add(idy, -w * lx);
        f[3].add(idy, w * lx * ly);
      }
      else {
        const auto &[x, y, qid, plus] = sum[j++];
        T s[4];
        for(int i = 0, idy = id(y); i < 4; i++) { s[i] = f[i].sum(0, idy); }
        const T tmp = s[0] * x * y + s[1] * x + s[2] * y + s[3];
        ans[qid] += (plus ? tmp : -tmp);
      }
    }
    return ans;
  }
};
