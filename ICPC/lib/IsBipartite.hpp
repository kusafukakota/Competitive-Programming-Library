#pragma once

vector<ll> isBipartite(vector<vector<ll>> &g) {
  ll n = g.size();
  vector<ll> color(n, -1);
  function<bool(ll, ll)> DFS = [&](ll v, ll c) {
    color[v] = c;
    for(auto &nv : g[v]) {
      if(color[nv] != -1) {
        if(color[nv] == c) { return false; }
        continue;
      }
      if(!DFS(nv, 1 - c)) { return false; }
    }
    return true;
  };
  for(ll i = 0; i < n; i++) {
    if(color[i] == -1) {
      if(!DFS(i, 0)) { return {}; }
    }
  }
  return color;
}