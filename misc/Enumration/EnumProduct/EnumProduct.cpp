vector<vector<ll>> EnumProduct(vector<ll> v) {
  vector<vector<ll>> r;
  int N = ssize(v);
  auto DFS = [&](auto &&DFS, vector<ll> &p) -> void {
    int n = ssize(p);
    if(n == N) {
      r.emplace_back(p);
      return;
    }
    for(ll i = 0; i < v[n]; i++) {
      p.emplace_back(i);
      DFS(DFS, p);
      p.pop_back();
    }
  };
  vector<ll> p;
  DFS(DFS, p);
  return r;
}
