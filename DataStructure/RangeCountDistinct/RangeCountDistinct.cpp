template<typename T> struct RangeCountDistinct {
 private:
  int N, Q;
  vector<T> v;
  vector<pair<int, int>> qs;

 public:
  RangeCountDistinct(): RangeCountDistinct(vector<T>{}) {}
  explicit RangeCountDistinct(const vector<T> &v): N(v.size()), Q(0), v(v) {}
  void reserve(int Q) { qs.reserve(Q); }
  int query(int l, int r) {
    assert(0 <= l && l <= r && r <= N);
    qs.emplace_back(l, r);
    return Q++;
  }
  vector<int> solve() const {
    unordered_map<T, int> last;
    vector<int> prv(N), idx(N + 2), iq(Q), ans(Q);
    for(int i = 0; i < N; i++) { prv[i] = exchange(last[v[i]], i + 1); }
    for(auto &[l, r] : qs) { idx[r]++; }
    for(int i = 1; i <= N; i++) { idx[i] += idx[i - 1]; }
    idx[N + 1] = Q;
    for(int i = 0; i < Q; i++) { iq[--idx[qs[i].second]] = i; }
    fenwick_tree<int> f(N + 1);
    for(int r = 0; r <= N; r++) {
      for(int i = idx[r]; i < idx[r + 1]; i++) {
        const int id = iq[i], l = qs[id].first;
        ans[id] = f.sum(0, l + 1) - l;
      }
      if(r < N) { f.add(prv[r], 1); }
    }
    return ans;
  }
};
