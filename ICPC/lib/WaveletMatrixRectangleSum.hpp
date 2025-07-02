#pragma once

#include <lib/SuccinctIndexableDictionary.hpp>

template<typename T, int MAXLOG> struct WaveletMatrixRectangleSum {
  int len;
  SuccinctIndexableDictionary mat[MAXLOG];
  vector<T> ws[MAXLOG];
  int mid[MAXLOG];
  WaveletMatrixRectangleSum() = default;
  WaveletMatrixRectangleSum(const vector<T> &v, const vector<T> &w): len(v.size()) {
    assert(v.size() == w.size());
    vector<int> l(len), r(len), ord(len);
    iota(ord.begin(), ord.end(), 0);
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
      ws[lev].resize(len + 1);
      ws[lev][0] = 0;
      for(int i = 0; i < len; i++) { ws[lev][i + 1] = ws[lev][i] + w[ord[i]]; }
    }
  }
  pair<int, int> succ(bool f, int l, int r, int lev) { return {mat[lev].rank(f, l) + mid[lev] * f, mat[lev].rank(f, r) + mid[lev] * f}; }
  T sum(int l, int r, T upper) {
    T ret = 0;
    for(int lev = MAXLOG - 1; lev >= 0; lev--) {
      bool f = (upper >> lev) & 1;
      if(f) { ret += ws[lev][mat[lev].rank(false, r)] - ws[lev][mat[lev].rank(false, l)]; }
      tie(l, r) = succ(f, l, r, lev);
    }
    return ret;
  }
  T sum(int l, int r, T lower, T upper) { return sum(l, r, upper) - sum(l, r, lower); }
};

template<typename T = ll, int MAXLOG = 20> struct CompressedWaveletMatrixRectangleSum {
  WaveletMatrixRectangleSum<T, MAXLOG> mat;
  vector<T> ys;
  CompressedWaveletMatrixRectangleSum(const vector<T> &v, const vector<T> &w): ys(v) {
    ranges::sort(ys);
    ys.erase(unique(ys.begin(), ys.end()), ys.end());
    vector<T> t(v.size());
    for(int i = 0; i < (int)v.size(); i++) { t[i] = get(v[i]); }
    mat = WaveletMatrixRectangleSum<ll, MAXLOG>(t, w);
  }
  inline int get(const T &x) { return ranges::lower_bound(ys, x) - ys.begin(); }
  T sum(int l, int r, T upper) { return mat.sum(l, r, get(upper)); }
  T sum(int l, int r, T lower, T upper) { return mat.sum(l, r, get(lower), get(upper)); }
};