template<typename T> vector<ll> sort(vector<vector<pair<ll, T>>> &g) {
  ll n = g.size();
  vector<ll> r, e(n);
  priority_queue<ll, vector<ll>, greater<ll>> q;
  for(ll i = 0; i < n; i++) {
    for(auto &v : g[i]) { e[v.second]++; }
  }
  for(ll i = 0; i < n; i++) {
    if(e[i] == 0) { q.emplace(i); }
  }
  while(!q.empty()) {
    ll v = q.top();
    q.pop();
    r.emplace_back(v);
    for(auto &[nv, c] : g[v]) {
      e[nv]--;
      if(e[nv] == 0) { q.emplace(nv); }
    }
  }
  return r;
}
