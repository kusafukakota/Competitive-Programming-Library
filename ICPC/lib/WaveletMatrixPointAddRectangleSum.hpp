#pragma once

struct SuccinctIndexableDictionary {
  unsigned len, blk;
  vector<unsigned> bit, sum;
  SuccinctIndexableDictionary() = default;
  SuccinctIndexableDictionary(unsigned len): len(len), blk((len + 31) >> 5) {
    bit.assign(blk, 0U);
    sum.assign(blk, 0U);
  }
  void set(int k) { bit[k >> 5] |= 1U << (k & 31); }
  void build() {
    sum[0] = 0U;
    for(unsigned i = 1; i < blk; i++) { sum[i] = sum[i - 1] + __builtin_popcount(bit[i - 1]); }
  }
  bool operator[](ll k) { return (bool((bit[k >> 5] >> (k & 31)) & 1)); }
  int rank(int k) { return (sum[k >> 5] + __builtin_popcount(bit[k >> 5] & ((1U << (k & 31)) - 1))); }
  int rank(bool val, int k) { return (val ? rank(k) : k - rank(k)); }
};

template<typename T, int MAXLOG> struct WaveletMatrixPointAddRectangleSum {
  int len;
  SuccinctIndexableDictionary mat[MAXLOG];
  fenwick_tree<T> ws[MAXLOG];
  vector<T> v;
  int mid[MAXLOG];
  WaveletMatrixPointAddRectangleSum() = default;
  WaveletMatrixPointAddRectangleSum(const vector<T> &v, const vector<T> &w): len(v.size()), v(v) {
    assert(v.size() == w.size());
    vector<int> l(len), r(len), ord(len);
    iota(ord.begin(), ord.end(), 0);
    vector<T> dd(len);
    for(int lev = MAXLOG - 1; lev >= 0; lev--) {
      mat[lev] = SuccinctIndexableDictionary(len + 1);
      int left = 0, right = 0;
      for(int i = 0; i < len; i++) {
        if((v[ord[i]] >> lev) & 1) {
          mat[lev].set(i);
          r[right++] = ord[i];
        }
        else { l[left++] = ord[i]; }
      }
      mid[lev] = left;
      mat[lev].build();
      ord.swap(l);
      for(int i = 0; i < right; i++) { ord[left + i] = r[i]; }
      for(int i = 0; i < len; i++) { dd[i] = w[ord[i]]; }
      ws[lev] = fenwick_tree<T>(dd);
    }
  }
  pair<int, int> succ(bool f, int l, int r, int lev) { return {mat[lev].rank(f, l) + mid[lev] * f, mat[lev].rank(f, r) + mid[lev] * f}; }
  void add(int k, const T &x) {
    auto &y = v[k];
    for(int lev = MAXLOG - 1; lev >= 0; lev--) {
      bool f = (y >> lev) & 1;
      k = mat[lev].rank(f, k) + mid[lev] * f;
      ws[lev].apply(k, x);
    }
  }
  T sum(int l, int r, T upper) {
    T ret = 0;
    for(int lev = MAXLOG - 1; lev >= 0; lev--) {
      if((upper >> lev) & 1) {
        auto nx = succ(false, l, r, lev);
        ret += ws[lev].prod(nx.first, nx.second);
        l = l - nx.first + mid[lev];
        r = r - nx.second + mid[lev];
      }
      else { tie(l, r) = succ(false, l, r, lev); }
    }
    return ret;
  }
  T sum(int l, int r, T lower, T upper) { return sum(l, r, upper) - sum(l, r, lower); }
};

template<typename T = ll, int MAXLOG = 20> struct CompressedWaveletMatrixPointAddRectangleSum {
  WaveletMatrixPointAddRectangleSum<int, MAXLOG> mat;
  vector<T> ys;
  CompressedWaveletMatrixPointAddRectangleSum(const vector<T> &v, const vector<T> &w): ys(v) {
    ranges::sort(ys);
    ys.erase(unique(ys.begin(), ys.end()), ys.end());
    vector<T> t(v.size());
    for(int i = 0; i < (int)v.size(); i++) { t[i] = get(v[i]); }
    mat = WaveletMatrixPointAddRectangleSum<T, MAXLOG>(t, w);
  }
  inline int get(const T &x) { return lower_bound(begin(ys), end(ys), x) - begin(ys); }
  void add(int k, const T &x) { mat.add(k, x); }
  T sum(int l, int r, T upper) { return mat.sum(l, r, get(upper)); }
  T sum(int l, int r, T lower, T upper) { return mat.sum(l, r, get(lower), get(upper)); }
};