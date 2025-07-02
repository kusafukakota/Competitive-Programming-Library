#pragma once

#include <lib/SuccinctIndexableDictionary.hpp>

template<typename T, ll MAXLOG> struct WaveletMatrix {
  ll len;
  SuccinctIndexableDictionary mat[MAXLOG];
  ll mid[MAXLOG];
  WaveletMatrix() = default;
  WaveletMatrix(vector<T> v): len(v.size()) {
    vector<T> l(len), r(len);
    for(ll lev = MAXLOG - 1; lev >= 0; lev--) {
      mat[lev] = SuccinctIndexableDictionary(len + 1);
      ll left = 0, right = 0;
      for(ll i = 0; i < len; i++) {
        if(((v[i] >> lev) & 1)) {
          mat[lev].set(i);
          r[right++] = v[i];
        }
        else { l[left++] = v[i]; }
      }
      mid[lev] = left;
      mat[lev].build();
      v.swap(l);
      for(ll i = 0; i < right; i++) { v[left + i] = r[i]; }
    }
  }
  pair<ll, ll> succ(bool f, ll l, ll r, ll lev) { return {mat[lev].rank(f, l) + mid[lev] * f, mat[lev].rank(f, r) + mid[lev] * f}; }
  T access(ll k) {
    T ret = 0;
    for(ll lev = MAXLOG - 1; lev >= 0; lev--) {
      bool f = mat[lev][k];
      if(f) { ret |= T(1) << lev; }
      k = mat[lev].rank(f, k) + mid[lev] * f;
    }
    return ret;
  }
  T operator[](const ll &k) { return access(k); }
  ll rank(const T &x, ll r) {
    ll l = 0;
    for(ll lev = MAXLOG - 1; lev >= 0; lev--) { tie(l, r) = succ((x >> lev) & 1, l, r, lev); }
    return r - l;
  }
  T kth_smallest(ll l, ll r, ll k) {
    assert(0 <= k && k < r - l);
    T ret = 0;
    for(ll lev = MAXLOG - 1; lev >= 0; lev--) {
      ll cnt = mat[lev].rank(false, r) - mat[lev].rank(false, l);
      bool f = cnt <= k;
      if(f) {
        ret |= T(1) << lev;
        k -= cnt;
      }
      tie(l, r) = succ(f, l, r, lev);
    }
    return ret;
  }
  T kth_largest(ll l, ll r, ll k) { return kth_smallest(l, r, r - l - k - 1); }
  ll range_freq(ll l, ll r, T upper) {
    ll ret = 0;
    for(ll lev = MAXLOG - 1; lev >= 0; lev--) {
      bool f = ((upper >> lev) & 1);
      if(f) { ret += mat[lev].rank(false, r) - mat[lev].rank(false, l); }
      tie(l, r) = succ(f, l, r, lev);
    }
    return ret;
  }
  ll range_freq(ll l, ll r, T lower, T upper) { return range_freq(l, r, upper) - range_freq(l, r, lower); }
  T prev_value(ll l, ll r, T upper) {
    ll cnt = range_freq(l, r, upper);
    return cnt == 0 ? T(-1) : kth_smallest(l, r, cnt - 1);
  }
  T next_value(ll l, ll r, T lower) {
    ll cnt = range_freq(l, r, lower);
    return cnt == r - l ? T(-1) : kth_smallest(l, r, cnt);
  }
};

template<typename T = ll, ll MAXLOG = 20> struct CompressedWaveletMatrix {
  WaveletMatrix<ll, MAXLOG> mat;
  vector<T> ys;
  CompressedWaveletMatrix() {}
  CompressedWaveletMatrix(const vector<T> &v): ys(v) {
    ranges::sort(ys);
    ys.erase(unique(ys.begin(), ys.end()), ys.end());
    vector<ll> t(v.size());
    for(ll i = 0; i < (ll)v.size(); i++) { t[i] = get(v[i]); }
    mat = WaveletMatrix<ll, MAXLOG>(t);
  }
  inline ll get(const T &x) { return ranges::lower_bound(ys, x) - ys.begin(); }
  T access(ll k) { return ys[mat.access(k)]; }
  T operator[](const ll &k) { return access(k); }
  ll rank(const T &x, ll r) {
    auto pos = get(x);
    if(pos == (ll)ys.size() || ys[pos] != x) { return 0; }
    return mat.rank(pos, r);
  }
  // return ＃{i∈[l, r) | v[i] == x}
  ll count(ll l, ll r, T x) {
    if(l >= r) { return 0; }
    return rank(x, r) - rank(x, l);
  }
  // return k-th(0-indexed) smallest number in v[i] s.t. i∈[l, r)
  T kth_smallest(ll l, ll r, ll k) { return ys[mat.kth_smallest(l, r, k)]; }
  // return k-th(0-indexed) largest number in v[i] s.t. i∈[l, r)
  T kth_largest(ll l, ll r, ll k) { return ys[mat.kth_largest(l, r, k)]; }
  // return ＃{i∈[l, r) | v[i] < upper}
  ll range_freq(ll l, ll r, T upper) {
    if(l >= r) { return 0; }
    return mat.range_freq(l, r, get(upper));
  }
  // return ＃{i∈[l, r) | lower <= v[i] < upper}
  ll range_freq(ll l, ll r, T lower, T upper) {
    if(l >= r || lower >= upper) { return 0; }
    return mat.range_freq(l, r, get(lower), get(upper));
  }
  // return max v[i] s.t. i∈[l, r) && v[i] < upper
  T prev_value(ll l, ll r, T upper) {
    auto ret = mat.prev_value(l, r, get(upper));
    return ret == -1 ? T(-1) : ys[ret];
  }
  // return min v[i] s.t. i∈[l, r) && lower <= v[i]
  T next_value(ll l, ll r, T lower) {
    auto ret = mat.next_value(l, r, get(lower));
    return ret == -1 ? T(-1) : ys[ret];
  }
};
