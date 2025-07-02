#pragma once

struct Namori {
  ll path_len;
  vector<ll> path, loop;
  Namori(const vector<ll> &nx, ll s = 0) {
    vector<ll> vis(nx.size(), -1);
    for(ll i = 0, p = s;; i++, p = nx[p]) {
      if(vis[p] != -1) {
        path_len = vis[p];
        break;
      }
      loop.emplace_back(p);
      vis[p] = i;
    }
    for(ll i = 0; i < path_len; i++) { path.emplace_back(loop[i]); }
    loop.erase(loop.begin(), loop.begin() + path_len);
  }
  inline ll operator()(ll k) const { return k < path_len ? path[k] : loop[(k - path_len) % loop.size()]; }
};