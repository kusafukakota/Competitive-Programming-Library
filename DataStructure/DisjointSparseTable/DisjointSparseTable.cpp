template<typename S, auto op, auto e> struct DisjointSparseTable {
  vector<vector<S>> t;
  DisjointSparseTable() {}
  DisjointSparseTable(const vector<S> &v) {
    const int N = v.size() + 2;
    const int H = 32 - __builtin_clz(N - 1);
    t.assign(H, vector<S>(N, e()));
    for(int k = 1; k < H; k++) {
      auto &s = t[k];
      const int W = 1 << k;
      for(int i = W; i < N; i += W * 2) {
        for(int j = i - 1; j > i - W; j--) { s[j - 1] = op(v[j - 1], s[j]); }
        const int M = min(i + W - 1, N - 1);
        for(int j = i; j < M; j++) { s[j + 1] = op(s[j], v[j - 1]); }
      }
    }
  }
  S get(int i) const { return prod(i, i + 1); }
  S prod(int l, int r) const {
    assert(0 <= l && l <= r && r <= ssize(t[0]) - 2);
    r++;
    const auto &s = t[31 - __builtin_clz(l ^ r)];
    return op(s[l], s[r]);
  }
};
