#pragma once

#include <lib/Tree.hpp>

// https://nyaannyaan.github.io/library/tree/static-top-tree-vertex-based.hpp
enum Type { Vertex,
            Compress,
            Rake,
            Add_Edge,
            Add_Vertex };

struct StaticTopTreeBase {
 private:
  int add(int l, int r, Type t) {
    if(t == Type::Compress || t == Type::Rake) { assert(l != -1 && r != -1); }
    if(t == Type::Add_Edge) { assert(l != -1 && r == -1); }
    assert(t != Type::Vertex && t != Type::Add_Vertex);
    int k = P.size();
    P.push_back(-1), L.push_back(l), R.push_back(r), T.push_back(t);
    if(l != -1) { P[l] = k; }
    if(r != -1) { P[r] = k; }
    return k;
  }
  int add2(int k, int l, int r, Type t) {
    assert(k < (int)g.size());
    assert(t == Type::Vertex || t == Type::Add_Vertex);
    if(t == Type::Vertex) { assert(l == -1 && r == -1); }
    else { assert(l != -1 && r == -1); }
    P[k] = -1, L[k] = l, R[k] = r, T[k] = t;
    if(l != -1) { P[l] = k; }
    if(r != -1) { P[r] = k; }
    return k;
  }
  pair<int, int> merge(const vector<pair<int, int>> &a, Type t) {
    assert(!a.empty());
    if(a.size() == 1) { return a[0]; }
    int sum = 0;
    for(auto &[_, s] : a) { sum += s; }
    vector<pair<int, int>> b, c;
    for(auto &[i, s] : a) {
      (sum > s ? b : c).emplace_back(i, s);
      sum -= 2 * s;
    }
    auto [i, si] = merge(b, t);
    auto [j, sj] = merge(c, t);
    return {add(i, j, t), si + sj};
  }
  pair<int, int> compress(int i) {
    vector<pair<int, int>> chs;
    while(true) {
      chs.push_back(add_vertex(i));
      if(g[i].empty()) { break; }
      i = g[i][0];
    }
    return merge(chs, Type::Compress);
  }
  pair<int, int> rake(int i) {
    vector<pair<int, int>> chs;
    for(int j = 1; j < (int)g[i].size(); j++) { chs.push_back(add_edge(g[i][j])); }
    if(chs.empty()) { return {-1, 0}; }
    return merge(chs, Type::Rake);
  }
  pair<int, int> add_edge(int i) {
    auto [j, sj] = compress(i);
    return {add(j, -1, Type::Add_Edge), sj};
  }
  pair<int, int> add_vertex(int i) {
    auto [j, sj] = rake(i);
    return {add2(i, j, -1, j == -1 ? Type::Vertex : Type::Add_Vertex), sj + 1};
  }
  void build() {
    auto [i, n] = compress(root);
    assert((int)g.size() == n);
    tt_root = i;
  }

 public:
  vector<vector<int>> g;
  int root, tt_root;
  vector<int> P, L, R;
  vector<Type> T;
  StaticTopTreeBase(const Tree &t, int r = 0): g(t.size()), root(r), P(t.size(), -1), L(t.size(), -1), R(t.size(), -1), T(t.size(), Type::Vertex) {
    const int N = g.size();
    vector<char> f(N, false);
    f[root] = true;
    queue<int> q;
    q.emplace(root);
    while(!q.empty()) {
      auto v = q.front();
      q.pop();
      for(auto &nv : t[v]) {
        if(!f[nv]) {
          f[nv] = true;
          q.push(nv);
          g[v].push_back(nv);
        }
      }
    }
    build();
  }
};

template<typename Path, typename Point, typename Vertex, typename Compress, typename Rake, typename Add_Edge, typename Add_Vertex> struct StaticTopTree {
 private:
  void inner_update(int k) {
    if(tt.T[k] == Type::Vertex) { path[k] = vertex(k); }
    if(tt.T[k] == Type::Compress) { path[k] = compress(path[tt.L[k]], path[tt.R[k]]); }
    if(tt.T[k] == Type::Rake) { point[k] = rake(point[tt.L[k]], point[tt.R[k]]); }
    if(tt.T[k] == Type::Add_Edge) { point[k] = add_edge(path[tt.L[k]]); }
    if(tt.T[k] == Type::Add_Vertex) { path[k] = add_vertex(point[tt.L[k]], k); }
  }
  void dfs(int k) {
    if(tt.L[k] != -1) { dfs(tt.L[k]); }
    if(tt.R[k] != -1) { dfs(tt.R[k]); }
    inner_update(k);
  }

 public:
  const StaticTopTreeBase tt;
  vector<Path> path;
  vector<Point> point;
  const Vertex vertex;
  const Compress compress;
  const Rake rake;
  const Add_Edge add_edge;
  const Add_Vertex add_vertex;
  StaticTopTree(const Tree &g, const Vertex &vertex, const Compress &compress, const Rake &rake, const Add_Edge &add_edge, const Add_Vertex &add_vertex, int r = 0): tt(g, r), vertex(vertex), compress(compress), rake(rake), add_edge(add_edge), add_vertex(add_vertex) {
    const int n = tt.P.size();
    path.resize(n);
    point.resize(n);
    dfs(tt.tt_root);
  }
  Path get() { return path[tt.tt_root]; }
  void update(int k) {
    for(; k != -1; k = tt.P[k]) { inner_update(k); }
  }
};