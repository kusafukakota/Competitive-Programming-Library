#include <bits/stdc++.h>
using namespace std;
using ll = long long;

struct SuccinctIndexableDictionary {
  ll len;
  ll blk;
  vector<ll> bit, sum;
  SuccinctIndexableDictionary() = default;
  SuccinctIndexableDictionary(ll len): len(len), blk((len + 31) >> 5) {
    bit.assign(blk, 0LL);
    sum.assign(blk, 0LL);
  }
  void set(ll k) { bit[k >> 5] |= 1LL << (k & 31); }
  void build() {
    sum[0] = 0LL;
    for(ll i = 1; i < blk; i++) sum[i] = sum[i - 1] + __builtin_popcountll(bit[i - 1]);
  }
  bool operator[](ll k) { return (bool((bit[k >> 5] >> (k & 31)) & 1)); }
  ll rank(ll k) { return (sum[k >> 5] + __builtin_popcountll(bit[k >> 5] & ((1LL << (k & 31)) - 1))); }
  ll rank(bool val, ll k) { return (val ? rank(k) : k - rank(k)); }
};

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
        else l[left++] = v[i];
      }
      mid[lev] = left;
      mat[lev].build();
      v.swap(l);
      for(ll i = 0; i < right; i++) v[left + i] = r[i];
    }
  }
  pair<ll, ll> succ(bool f, ll l, ll r, ll lev) { return {mat[lev].rank(f, l) + mid[lev] * f, mat[lev].rank(f, r) + mid[lev] * f}; }
  T access(ll k) {
    T ret = 0;
    for(ll lev = MAXLOG - 1; lev >= 0; lev--) {
      bool f = mat[lev][k];
      if(f) ret |= T(1) << lev;
      k = mat[lev].rank(f, k) + mid[lev] * f;
    }
    return ret;
  }
  T operator[](const ll &k) { return access(k); }
  ll rank(const T &x, ll r) {
    ll l = 0;
    for(ll lev = MAXLOG - 1; lev >= 0; lev--) tie(l, r) = succ((x >> lev) & 1, l, r, lev);
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
      if(f) ret += mat[lev].rank(false, r) - mat[lev].rank(false, l);
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
  CompressedWaveletMatrix(const vector<T> &v): ys(v) {
    ranges::sort(ys);
    ys.erase(unique(ys.begin(), ys.end()), ys.end());
    vector<ll> t(v.size());
    for(ll i = 0; i < (ll)v.size(); i++) t[i] = get(v[i]);
    mat = WaveletMatrix<ll, MAXLOG>(t);
  }
  inline ll get(const T &x) { return ranges::lower_bound(ys, x) - ys.begin(); }
  T access(ll k) { return ys[mat.access(k)]; }
  T operator[](const ll &k) { return access(k); }
  ll rank(const T &x, ll r) {  // count i s.t. (0<=i<r)&&v[i]==x
    auto pos = get(x);
    if(pos == (ll)ys.size() || ys[pos] != x) return 0;
    return mat.rank(pos, r);
  }
  ll count(ll l, ll r, T x) {  // count i s.t. (l<=i<r)&&v[i]==x
    if(l >= r) { return 0; }
    return rank(x, r) - rank(x, l);
  }
  T kth_smallest(ll l, ll r, ll k) { return ys[mat.kth_smallest(l, r, k)]; }  // k-th(0-indexed) smallest number in v[l,r)
  T kth_largest(ll l, ll r, ll k) { return ys[mat.kth_largest(l, r, k)]; }  // k-th(0-indexed) largest number in v[l,r)
  ll range_freq(ll l, ll r, T upper) {  // count i s.t. (l<=i<r)&&(v[i]<upper)
    if(l >= r) { return 0; }
    return mat.range_freq(l, r, get(upper));
  }
  ll range_freq(ll l, ll r, T lower, T upper) {  // count i s.t. (l<=i<r)&&(lower<=v[i]<upper)
    if(l >= r || lower >= upper) { return 0; }
    return mat.range_freq(l, r, get(lower), get(upper));
  }
  T prev_value(ll l, ll r, T upper) {  // max v[i] s.t. (l<=i<r)&&(v[i]<upper)
    auto ret = mat.prev_value(l, r, get(upper));
    return ret == -1 ? T(-1) : ys[ret];
  }
  T next_value(ll l, ll r, T lower) {  // min v[i] s.t. (l<=i<r)&&(lower<=v[i])
    auto ret = mat.next_value(l, r, get(lower));
    return ret == -1 ? T(-1) : ys[ret];
  }
};

int main() {
  ios::sync_with_stdio(false);
  cin.tie(0);
  ll n;
  cin >> n;
  vector<ll> a(n);
  for(auto &i : a) {
    cin >> i;
    i--;
  }
  CompressedWaveletMatrix<> w(a);
  vector<array<ll, 4>> v = {{0, n, 0, n}};
  ll q;
  cin >> q;
  while(q--) {
    ll t, s, x;
    cin >> t >> s >> x;
    auto [l, r, a, b] = v[s];
    if(t == 1) {
      auto p = [&]() {
        for(ll L = l, R = r + 1;;) {
          if(R - L <= 1) { return L; }
          ll M = (L + R) / 2, c = w.range_freq(l, M, a, b);
          c > x ? R = M : L = M;
        }
      }();
      v[s] = {l, p, a, b};
      v.push_back({p, r, a, b});
      cout << w.range_freq(p, r, a, b) << "\n";
    }
    else {
      v[s] = {l, r, a, min(x, b)};
      v.push_back({l, r, max(x, a), b});
      cout << w.range_freq(l, r, max(x, a), b) << "\n";
    }
  }
}
