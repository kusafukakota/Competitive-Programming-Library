#pragma once

struct Cycle {
 private:
  vector<int> used;
  int dfs(int v, int p) {
    if(used[v] == 1) { return v; }
    if(used[v] == 2) { return -1; }
    used[v] = 1;
    for(auto &[nv, id] : g[v]) {
      if(id == p) { continue; }
      int nxt = dfs(nv, id);
      if(nxt == -1) { continue; }
      if(nxt == -2) { return -2; }
      cycle.emplace_back(nv, id);
      if(nxt == v) { return -2; }
      return nxt;
    }
    used[v] = 2;
    return -1;
  }

 public:
  int N, e = 0;
  bool directed;
  vector<vector<pair<int, int>>> g;
  vector<pair<int, int>> cycle;  // {v, idx of e}
  Cycle() {}
  Cycle(int N, bool directed): N(N), g(N), used(N), directed(directed) {}
  void add_edge(int u, int v) {
    g[u].emplace_back(v, e);
    if(!directed) { g[v].emplace_back(u, e); }
    e++;
  }
  vector<pair<int, int>> build() {
    for(int i = 0; i < N; i++) {
      if(dfs(i, -1) == -2) {
        ranges::reverse(cycle);
        break;
      }
    }
    return cycle;
  }
};