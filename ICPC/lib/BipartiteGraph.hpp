#pragma once

// https://ei1333.github.io/library/graph/flow/bipartite-flow.hpp
struct BipartiteGraph {
 private:
  vector<int> find_residual_path() {
    auto res = build_residual_graph();
    queue<int> q;
    vector<int> vis(n + m + 2);
    q.emplace(n + m);
    vis[n + m] = true;
    while(!q.empty()) {
      int idx = q.front();
      q.pop();
      for(auto &to : res[idx]) {
        if(vis[to]) { continue; }
        vis[to] = true;
        q.emplace(to);
      }
    }
    return vis;
  }
  void build_augment_path() {
    queue<int> q;
    d.assign(g.size(), -1);
    for(int i = 0; i < n; i++) {
      if(l[i] == -1) {
        q.emplace(i);
        d[i] = 0;
      }
    }
    while(!q.empty()) {
      int a = q.front();
      q.pop();
      for(auto &b : g[a]) {
        int c = r[b];
        if(c >= 0 && d[c] == -1) {
          d[c] = d[a] + 1;
          q.emplace(c);
        }
      }
    }
  }
  bool find_minimum_dist_augment_path(int a) {
    used[a] = t;
    for(auto &b : g[a]) {
      int c = r[b];
      if(c < 0 || (used[c] != t && d[c] == d[a] + 1 && find_minimum_dist_augment_path(c))) {
        r[b] = a;
        l[a] = b;
        return true;
      }
    }
    return false;
  }
  bool find_augment_path(int a) {
    used[a] = t;
    for(auto &b : g[a]) {
      int c = r[b];
      if(c < 0 || (alive[c] == 1 && used[c] != t && find_augment_path(c))) {
        r[b] = a;
        l[a] = b;
        return true;
      }
    }
    return false;
  }

  int n, m, t;
  vector<vector<int>> g, rg;
  vector<int> l, r, d, used, alive;
  bool matched;

 public:
  explicit BipartiteGraph(int n, int m): n(n), m(m), t(0), g(n), rg(m), l(n, -1), r(m, -1), used(n), alive(n, 1), matched(false) {}
  void add_edge(int u, int v) {
    g[u].emplace_back(v);
    rg[v].emplace_back(u);
  }
  void erase_edge(int a, int b) {
    if(l[a] == b) {
      l[a] = -1;
      r[b] = -1;
    }
    g[a].erase(find(begin(g[a]), end(g[a]), b));
    rg[b].erase(find(begin(rg[b]), end(rg[b]), a));
  }
  vector<pair<int, int>> maximum_matching() {
    matched = true;
    while(true) {
      build_augment_path();
      t++;
      int f = 0;
      for(int i = 0; i < n; i++) {
        if(l[i] == -1) { f += find_minimum_dist_augment_path(i); }
      }
      if(!f) { break; }
    }
    vector<pair<int, int>> ret;
    for(int i = 0; i < n; i++) {
      if(l[i] >= 0) { ret.emplace_back(i, l[i]); }
    }
    return ret;
  }
  vector<pair<int, int>> lex_maximum_matching() {
    if(!matched) { maximum_matching(); }
    for(auto &vs : g) { ranges::sort(vs); }
    vector<pair<int, int>> es;
    for(int i = 0; i < n; i++) {
      if(l[i] == -1 || alive[i] == 0) { continue; }
      r[l[i]] = -1;
      l[i] = -1;
      t++;
      find_augment_path(i);
      alive[i] = 0;
      es.emplace_back(i, l[i]);
    }
    return es;
  }
  vector<int> minimum_vertex_cover() {
    auto vis = find_residual_path();
    vector<int> ret;
    for(int i = 0; i < n + m; i++) {
      if(vis[i] ^ (i < n)) { ret.emplace_back(i); }
    }
    return ret;
  }
  vector<int> lex_minimum_vertex_cover(const vector<int> &ord) {
    assert((int)ord.size() == n + m);
    auto res = build_residual_graph();
    vector<vector<int>> r_res(n + m + 2);
    for(int i = 0; i < n + m + 2; i++) {
      for(auto &j : res[i]) { r_res[j].emplace_back(i); }
    }
    queue<int> q;
    vector<int> vis(n + m + 2, -1);
    auto exp_l = [&](int t) {
      if(vis[t] != -1) { return; }
      q.emplace(t);
      vis[t] = 1;
      while(!q.empty()) {
        int idx = q.front();
        q.pop();
        for(auto &to : r_res[idx]) {
          if(vis[to] != -1) { continue; }
          vis[to] = 1;
          q.emplace(to);
        }
      }
    };
    auto exp_r = [&](int t) {
      if(vis[t] != -1) { return; }
      q.emplace(t);
      vis[t] = 0;
      while(!q.empty()) {
        int idx = q.front();
        q.pop();
        for(auto &to : res[idx]) {
          if(vis[to] != -1) { continue; }
          vis[to] = 0;
          q.emplace(to);
        }
      }
    };
    exp_r(n + m);
    exp_l(n + m + 1);
    vector<int> ret;
    for(auto &t : ord) {
      if(t < n) {
        exp_l(t);
        if(vis[t] & 1) { ret.emplace_back(t); }
      }
      else {
        exp_r(t);
        if(~vis[t] & 1) { ret.emplace_back(t); }
      }
    }
    return ret;
  }
  vector<int> maximum_independent_set() {
    auto vis = find_residual_path();
    vector<int> ret;
    for(int i = 0; i < (n + m); i++) {
      if(vis[i] ^ (i >= n)) { ret.emplace_back(i); }
    }
    return ret;
  }
  vector<pair<int, int>> minimum_edge_cover() {
    auto es = maximum_matching();
    for(int i = 0; i < n; i++) {
      if(l[i] >= 0) { continue; }
      if(g[i].empty()) { return {}; }
      es.emplace_back(i, g[i][0]);
    }
    for(int i = 0; i < m; i++) {
      if(r[i] >= 0) { continue; }
      if(rg[i].empty()) { return {}; }
      es.emplace_back(rg[i][0], i);
    }
    return es;
  }
  // left: [0,n), right: [n,n+m), S: n+m, T: n+m+1
  vector<vector<int>> build_residual_graph() {
    if(!matched) { maximum_matching(); }
    const int S = n + m, T = n + m + 1;
    vector<vector<int>> res(n + m + 2);
    for(int i = 0; i < n; i++) {
      if(l[i] == -1) { res[S].emplace_back(i); }
      else { res[i].emplace_back(S); }
    }
    for(int i = 0; i < m; i++) {
      if(r[i] == -1) { res[i + n].emplace_back(T); }
      else { res[T].emplace_back(i + n); }
    }
    for(int i = 0; i < n; i++) {
      for(auto &j : g[i]) {
        if(l[i] == j) { res[j + n].emplace_back(i); }
        else { res[i].emplace_back(j + n); }
      }
    }
    return res;
  }
};
