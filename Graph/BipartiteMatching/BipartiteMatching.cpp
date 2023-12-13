ll BipartiteMatching(vector<vector<ll>>& g) {
  ll n = g.size();
  vector<ll> color(n, -1);
  function<bool(ll, ll)> DFS = [&](ll v, ll c) {
    color[v] = c;
    for(auto &nv : g[v]) {
      if(color[nv] != -1) {
        if(color[nv] == c) {return false;}
        continue;
      }
      if(!DFS(nv, 1 - c)) {return false;}
    }
    return true;
  };
  for(ll i = 0; i < n; i++) {
    if(color[i] == -1) {
      if(!DFS(i, 0)) {return -1;}
    }
  }
  mf_graph<ll> f(n + 2);
  for(ll i = 0; i < n; i++) {
    !color[i] ? f.add_edge(n, i, 1) : f.add_edge(i, n + 1, 1);
    for(auto &j : g[i]) {
      if(i >= j) {continue;}
      !color[i] ? f.add_edge(i, j, 1) : f.add_edge(j, i, 1);
    }
  }
  return f.flow(n, n + 1);
}
