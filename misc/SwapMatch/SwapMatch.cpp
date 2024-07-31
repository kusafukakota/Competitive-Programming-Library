template<typename T> vector<T> Compress(vector<T> &v) {
  vector<T> r = v;
  ranges::sort(r);
  r.erase(unique(r.begin(), r.end()), r.end());
  for(auto &i : v) { i = ranges::lower_bound(r, i) - r.begin(); }
  return r;
}

ll Inversion(vector<ll> &v) {
  ll r = 0, n = v.size();
  // Compress(v);
  fenwick_tree<ll> b(n + 1);
  for(ll i = 0; i < n; i++) {
    r += b.sum(v[i] + 1, n + 1);
    b.add(v[i], 1);
  }
  return r;
}

ll SwapMatch(vector<ll> &A, vector<ll> &B, bool check = false) {
  if(check) {
    auto a = A, b = B;
    ranges::sort(a);
    ranges::sort(b);
    if(a != b) { return -1; }
  }
  if(A.empty()) { return 0; }
  auto a = A, b = B;
  Compress(a);
  Compress(b);
  ll N = A.size();
  vector<queue<ll>> q(ranges::max(a) + 1);
  vector<ll> v;
  for(ll i = 0; i < N; i++) { q[a[i]].emplace(i); }
  for(ll i = 0; i < N; i++) {
    v.emplace_back(q[b[i]].front());
    q[b[i]].pop();
  }
  return Inversion(v);
}
