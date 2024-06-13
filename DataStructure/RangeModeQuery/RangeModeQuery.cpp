template<typename T> struct RangeModeQuery {
 private:
  int len, bs, bn;
  vector<T> sorted;
  vector<int> a, pos, posinv, start;
  vector<pair<int, int>> modebs;

  const auto &querybs(int lb, int rb) const { return modebs[lb * (bn + 1) + rb]; }
  auto &querybs(int lb, int rb) { return modebs[lb * (bn + 1) + rb]; }
  int checkl(int v, int posid, int l) const { return start[v] <= posid && l <= pos[posid]; }
  int checkr(int v, int posid, int r) const { return posid < start[v + 1] && pos[posid] < r; }
  static int cld(int num, int den) { return (num + den - 1) / den; }
  static int fld(int num, int den) { return num / den; }

 public:
  RangeModeQuery() = default;
  explicit RangeModeQuery(const vector<T> &v): len(v.size()), bs(sqrt(len)), bn(cld(len, bs)) {
    sorted = v;
    ranges::sort(sorted);
    sorted.erase(unique(sorted.begin(), sorted.end()), sorted.end());
    const int k = sorted.size();
    a.resize(len);
    start.assign(k + 1, 0);
    for(int i = 0; i < len; i++) {
      a[i] = ranges::lower_bound(sorted, v[i]) - sorted.begin();
      start[a[i]]++;
    }
    for(int i = 0; i < k; i++) { start[i + 1] += start[i]; }
    pos.resize(len);
    posinv.resize(len);
    for(int i = len - 1; i >= 0; i--) {
      const int posid = --start[a[i]];
      pos[posid] = i;
      posinv[i] = posid;
    }
    modebs.assign((bn + 1) * (bn + 1), {0, 0});
    vector<int> freq(k);
    for(int lb = 0; lb <= bn; lb++) {
      freq.assign(k, 0);
      pair<int, int> mode{0, 0};
      for(int rb = lb + 1; rb <= bn; rb++) {
        const int lid = (rb - 1) * bs, rid = min(len, rb * bs);
        for(int i = lid; i < rid; i++) { mode = max(mode, {++freq[a[i]], a[i]}); }
        querybs(lb, rb) = mode;
      }
    }
  }

  pair<T, int> query(const int l, const int r) const {
    assert(0 <= l && l < r && r <= len);
    const int lb = cld(l, bs), rb = fld(r, bs);
    auto [freq, mode] = querybs(lb, rb);
    for(int i = l; i < min(r, lb * bs); ++i) {
      const int v = a[i], posid = posinv[i];
      if(!checkr(v, posid + freq, r)) { continue; }
      do { ++freq; } while(checkr(v, posid + freq, r));
      mode = v;
    }
    for(int i = r - 1; i >= max(l, rb * bs); --i) {
      const int v = a[i], posid = posinv[i];
      if(!checkl(v, posid - freq, l)) { continue; }
      do { ++freq; } while(checkl(v, posid - freq, l));
      mode = v;
    }
    return {sorted[mode], freq};
  }
  pair<T, int> operator()(int l, int r) const { return query(l, r); }
};
