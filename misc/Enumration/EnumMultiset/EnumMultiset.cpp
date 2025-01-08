vector<vector<ll>> EnumMultiset(int n, int k) {
  vector<vector<ll>> r;
  vector<ll> v(n);
  auto DFS = [&](auto &&DFS, int p, int s) -> void {
    if(p == n) {
      r.emplace_back(v);
      return;
    }
    for(ll i = s; i < k; i++) {
      v[p] = i;
      DFS(DFS, p + 1, i);
    }
  };
  DFS(DFS, 0, 0);
  return r;
}
