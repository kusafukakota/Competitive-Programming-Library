#pragma once

// https://nyaannyaan.github.io/library/tree/dsu-on-tree.hpp.html
template<typename G> struct DSUonTree {
 private:
  G &g;
  int N, id, root;
  vector<int> sz, euler, down, up;
  int dfs1(int v, int p = -1) {
    sz[v] = 1;
    if((int)g[v].size() >= 2 && g[v][0] == p) { swap(g[v][0], g[v][1]); }
    for(auto &nv : g[v]) {
      if(nv == p) { continue; }
      sz[v] += dfs1(nv, v);
      if(sz[nv] > sz[g[v][0]]) { swap(nv, g[v][0]); }
    }
    return sz[v];
  }
  void dfs2(int v, int p = -1) {
    euler[id] = v;
    down[v] = id++;
    for(auto &nv : g[v]) {
      if(nv == p) { continue; }
      dfs2(nv, v);
    }
    up[v] = id;
  }

 public:
  DSUonTree(G &g_, int root = 0): g(g_), N(g_.size()), sz(g_.size()), euler(g_.size()), down(g_.size()), up(g_.size()), id(0), root(root) {
    dfs1(root);
    dfs2(root);
  }
  int idx(int u) const { return down[u]; }
  template<typename U, typename Q, typename C, typename R> void run(U &update, Q &query, C &clear, R &reset) {
    auto dsu = [&](auto dsu, int v, int p = -1, bool keep = false) -> void {
      for(int i = 1; i < (int)g[v].size(); i++) {
        if(g[v][i] != p) { dsu(dsu, g[v][i], v, false); }
      }
      if(sz[v] != 1) { dsu(dsu, g[v][0], v, true); }
      if(sz[v] != 1) {
        for(int i = up[g[v][0]]; i < up[v]; i++) { update(euler[i]); }
      }
      update(v);
      query(v);
      if(!keep) {
        for(int i = down[v]; i < up[v]; i++) { clear(euler[i]); }
        reset();
      }
      return;
    };
    dsu(dsu, root);
  }
};
