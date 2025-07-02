#pragma once

#include <lib/Lowlink.hpp>

struct BiConnectedComponents : Lowlink {
 private:
  void build() {
    used.assign(this->g.size(), 0);
    for(int i = 0; i < ssize(used); i++) {
      if(!used[i]) { dfs(i, -1); }
    }
  }
  void dfs(int idx, int par) {
    used[idx] = true;
    for(auto &to : this->g[idx]) {
      if(to == par) { continue; }
      if(!used[to] || this->ord[to] < this->ord[idx]) { tmp.emplace_back(minmax<int>(idx, to)); }
      if(!used[to]) {
        dfs(to, idx);
        if(this->low[to] >= this->ord[idx]) {
          bc.emplace_back();
          while(true) {
            auto e = tmp.back();
            bc.back().emplace_back(e);
            tmp.pop_back();
            if(e.first == min<int>(idx, to) && e.second == max<int>(idx, to)) { break; }
          }
        }
      }
    }
  }

 public:
  vector<ll> used;
  vector<vector<pair<ll, ll>>> bc;
  vector<pair<ll, ll>> tmp;
  BiConnectedComponents(const vector<vector<ll>> &g): Lowlink(g) { build(); }
};