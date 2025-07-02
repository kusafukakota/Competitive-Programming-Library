#pragma once

#include <lib/Tree.hpp>

struct AuxiliaryTree : Tree {
  vector<vector<ll>> g;
  vector<ll> id, inv;
  AuxiliaryTree(const vector<vector<ll>> &g, ll r = 0): Tree(g, r), inv(g.size()) {}
  // v とそれらの LCA のみ含む木を構築．根を返す（構築後の木での頂点番号）
  int build(const vector<ll> &v) {
    int N = v.size();
    g.assign(N, vector<ll>());
    id = v;
    ranges::sort(id, [&](auto x, auto y) { return (*this).in(x) < (*this).in(y); });
    stack<int> s;
    s.emplace(id[0]);
    inv[id[0]] = 0;
    for(int i = 0; i < N - 1; i++) {
      int u = (*this).lca(id[i], id[i + 1]);
      if(u != id[i]) {
        int p = inv[s.top()];
        while(true) {
          s.pop();
          if(s.empty() || (*this).depth(u) >= (*this).depth(s.top())) { break; }
          int tmp = inv[s.top()];
          g[tmp].emplace_back(p);
          p = tmp;
        }
        if(s.empty() || s.top() != u) {
          s.emplace(u);
          id.emplace_back(u);
          inv[u] = g.size();
          g.push_back({p});
        }
        else { g[inv[u]].emplace_back(p); }
      }
      s.emplace(id[i + 1]);
      inv[id[i + 1]] = i + 1;
    }
    int p = ((s.size() > 1) ? inv[s.top()] : -1);
    while(s.size() > 1) {
      s.pop();
      int tmp = inv[s.top()];
      g[tmp].emplace_back(p);
      p = tmp;
    }
    return inv[s.top()];
  }
  // 木のサイズを返す
  ll size() { return g.size(); }
  inline vector<ll> operator[](ll i) { return g[i]; }
  // 元に木における頂点番号を返す
  inline ll operator()(ll i) { return id[i]; }
};