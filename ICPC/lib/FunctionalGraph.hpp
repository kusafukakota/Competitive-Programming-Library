#pragma once

struct FunctionalGraph {
 private:
  const int V;
  int id;
  vector<int> nx;
  void make_loop(const int s, int v, vector<int> &vec) {
    while(nx[v] != s) {
      vec.emplace_back(nx[v]);
      vis[nx[v]] = id;
      v = nx[v];
    }
  }
  int dfs(int v, vector<int> &vec) {
    vis[v] = -id;
    ll nv = nx[v];
    if(vis[nv] == -id) {
      vec.emplace_back(v);
      vec.emplace_back(nv);
      vis[v] = vis[nv] = id;
      make_loop(v, nv, vec);
      id++;
      return 0;
    }
    else if(!vis[nv]) {
      const int res = dfs(nv, vec);
      if(!res) { return 0; }
      else { return vis[v] = res; }
    }
    return vis[v] = (vis[nv] > 0 ? -vis[nv] : vis[nv]);
  }
  void make_graph() {
    graph.resize(V);
    for(int i = 0; i < V; i++) {
      if(vis[i] < 0) { graph[nx[i]].emplace_back(i); }
    }
  }

 public:
  vector<int> vis;
  vector<vector<int>> loop, graph;
  FunctionalGraph(const int N): V(N), id(1), nx(N, 0), vis(N, 0) {}
  template<typename T> FunctionalGraph(const vector<T> &v): V(v.size()), id(1), nx(V, 0), vis(V, 0) {
    for(int i = 0; i < V; i++) { add_edge(i, v[i]); }
    build();
  }
  void add_edge(int u, int v) {
    nx[u] = v;
    if(u == nx[u]) {
      vis[u] = id++;
      loop.push_back({u});
    }
  }
  void build() {
    for(int i = 0; i < V; i++) {
      if(!vis[i]) {
        vector<int> vec;
        dfs(i, vec);
        if(!vec.empty()) { loop.push_back(move(vec)); }
      }
    }
    make_graph();
  }
};