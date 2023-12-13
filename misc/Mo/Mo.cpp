struct Mo {
  ll W;
  vector<ll> L, R, O;
  Mo(ll N, ll Q): O(Q) {
    W = max<ll>(1LL, 1.0 * N / max<long double>(1.0, sqrt(Q * 2.0 / 3.0)));
    iota(O.begin(), O.end(), 0);
  }
  void operator()(ll l, ll r) {  // [l,r)
    L.emplace_back(l);
    R.emplace_back(r);
  }
  template<typename AL, typename AR, typename DL, typename DR, typename REM>
  void solve(const AL &add_l, const AR &add_r, const DL &del_l, const DR &del_r, const REM &rem) {
    sort(O.begin(), O.end(), [&](ll a, ll b) {
      ll A = L[a] / W, B = L[b] / W;
      if(A != B) { return A < B; }
      if(A & 1) { return R[a] < R[b]; }
      return R[a] > R[b];
    });
    ll nl = 0, nr = 0;
    for(auto i : O) {
      while(nl > L[i]) { add_l(--nl); }
      while(nr < R[i]) { add_r(nr++); }
      while(nl < L[i]) { del_l(nl++); }
      while(nr > R[i]) { del_r(--nr); }
      rem(i);
    }
  }
  template<typename AL, typename AR, typename DL, typename DR, typename REM>
  void operator()(const AL &add_l, const AR &add_r, const DL &del_l, const DR &del_r, const REM &rem) { solve(add_l, add_r, del_l, del_r, rem); }
  template<typename A, typename D, typename REM>
  void operator()(const A &add, const D &del, const REM &rem) { solve(add, add, del, del, rem); }
};

auto add = [&](ll i) {};
auto del = [&](ll i) {};
auto rem = [&](ll i) {};
