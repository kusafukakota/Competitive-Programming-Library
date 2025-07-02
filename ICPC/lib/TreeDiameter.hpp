#pragma once

// {{u, v}, w}
pair<pair<ll, ll>, ll> TreeDiameter(vector<vector<pair<ll, ll>>> &g) {
  vector<ll> D(g.size(), -1);
  function<void(ll, ll)> DFS = [&](ll v, ll d) {
    D[v] = d;
    for(auto &[nv, c] : g[v]) {
      if(D[nv] < 0) { DFS(nv, d + c); }
    }
  };
  DFS(0, 0);
  ll v = ranges::max_element(D) - D.begin();
  D.assign(g.size(), -1);
  DFS(v, 0);
  ll u = ranges::max_element(D) - D.begin();
  ll w = ranges::max(D);
  return {{u, v}, w};
}