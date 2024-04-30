template<typename S, typename T> struct CompressedInverseBIT2D {
 private:
  vector<array<S, 4>> rs;
  vector<T> ws;
  vector<array<S, 2>> ps;
  vector<int> ts;
  static int p2(int x) { return 1 << (31 - __builtin_clz(x)); }

 public:
  CompressedInverseBIT2D() = default;
  CompressedInverseBIT2D(int N, int Q) {
    rs.reserve(N);
    ws.reserve(N);
    ps.reserve(Q);
    ts.reserve(Q);
  }
  void add(S lx, S rx, S ly, S ry, T w) {
    assert(lx <= rx && ly <= ry);
    if(lx == rx || ly == ry) return;
    rs.push_back({lx, rx, ly, ry});
    ws.push_back(w);
  }
  void get(S x, S y) {
    ps.push_back({x, y});
    ts.push_back(rs.size());
  }
  vector<T> solve() const {
    vector<T> ans(ps.size());
    const int N = rs.size();
    using Key = pair<S, int>;
    constexpr auto comp = [](const Key &k1, const Key &k2) { return k1.first < k2.first; };
    vector<Key> esx(2 * N), esy(2 * N);
    for(int i = 0; i < N; i++) {
      esx[2 * i] = Key{rs[i][0], 2 * i};
      esx[2 * i + 1] = Key{rs[i][1], 2 * i + 1};
      esy[2 * i] = Key{rs[i][2], 2 * i};
      esy[2 * i + 1] = Key{rs[i][3], 2 * i + 1};
    }
    vector<vector<Key>> psx(N), psy(N);
    for(int pid = 0; pid < (int)ps.size(); pid++)
      if(ts[pid]) {
        const int r = p2(ts[pid]);
        psx[r - 1].emplace_back(ps[pid][0], pid);
        psy[r - 1].emplace_back(ps[pid][1], pid);
      }
    vector<int> pscy(ps.size()), escy(2 * N);
    for(int r = 1; r <= N; r++) {
      const int w = -r & r, l = r - w;
      for(int t = 1; t < w; t <<= 1) {
        auto irx = esx.begin() + 2 * r, imx = irx - 2 * t, ilx = imx - 2 * t;
        inplace_merge(ilx, imx, irx, comp);
        auto iry = esy.begin() + 2 * r, imy = iry - 2 * t, ily = imy - 2 * t;
        inplace_merge(ily, imy, iry, comp);
      }
      const int n = psx[r - 1].size();
      if(!n) { continue; }
      if(r == (-r & r)) {
        ranges::sort(psx[r - 1], comp);
        ranges::sort(psy[r - 1], comp);
      }
      int ny = 0;
      {
        vector<Key> mixy(esy.begin() + 2 * l, esy.begin() + 2 * r);
        const int msiz = mixy.size(), siz = msiz + n;
        mixy.reserve(siz);
        for(const auto &[y, pid] : psy[r - 1]) { mixy.emplace_back(y, ~pid); }
        inplace_merge(mixy.begin(), mixy.begin() + msiz, mixy.end(), comp);
        for(int t = 0; t < siz; t++) {
          const Key pkey = t ? mixy[t - 1] : Key{0, 0}, key = mixy[t];
          ny += t && comp(pkey, key) && (pkey.second < 0) && (key.second >= 0);
          const int i = key.second;
          (i >= 0 ? escy[i] : pscy[~i]) = ny;
        }
        ny++;
      }
      fenwick_tree<T> ft(ny);
      for(int j = 0, i = 2 * l; j < n; j++) {
        const auto &[px, pid] = psx[r - 1][j];
        for(; i < 2 * r; i++) {
          const auto &[ex, eid] = esx[i];
          if(px < ex) { break; }
          const T &w = ws[eid >> 1];
          ft.add(escy[eid & ~1], (eid & 1) ? -w : +w);
          ft.add(escy[eid | 1], (eid & 1) ? +w : -w);
        }
        ans[pid] += ft.sum(0, pscy[pid] + 1);
      }
      for(Key &key : psx[r - 1]) {
        if(int d = ts[key.second] - r) { psx[r + p2(d) - 1].push_back(move(key)); }
      }
      psx[r - 1].clear();
      psx[r - 1].shrink_to_fit();
      for(Key &key : psy[r - 1]) {
        if(int d = ts[key.second] - r) { psy[r + p2(d) - 1].push_back(move(key)); }
      }
      psy[r - 1].clear();
      psy[r - 1].shrink_to_fit();
    }
    return ans;
  }
};
