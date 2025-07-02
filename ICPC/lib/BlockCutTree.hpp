#pragma once

#include <lib/BiConnectedComponents.hpp>

struct BlockCutTree {
 private:
  void build() {
    auto ar = bcc.articulation;
    idar.resize(g.size(), -1);
    idcc.resize(g.size(), -1);
    for(int i = 0; i < ssize(ar); i++) { idar[ar[i]] = i; }
    tree.resize(ar.size() + bcc.bc.size());
    vector<int> last(g.size(), -1);
    for(int i = 0; i < ssize(bcc.bc); i++) {
      vector<int> st;
      for(auto &[u, v] : bcc.bc[i]) {
        st.emplace_back(u);
        st.emplace_back(v);
      }
      for(auto &u : st) {
        if(idar[u] == -1) { idcc[u] = i + ar.size(); }
        else if(last[u] != i) {
          add(i + ar.size(), idar[u]);
          last[u] = i;
        }
      }
    }
  }
  void add(int i, int j) {
    if(i == -1 || j == -1) { return; }
    tree[i].emplace_back(j);
    tree[j].emplace_back(i);
  }

 public:
  const vector<vector<ll>> &g;
  BiConnectedComponents bcc;
  vector<vector<ll>> tree;
  vector<ll> idar, idcc;
  BlockCutTree(const vector<vector<ll>> &g): g(g), bcc(g) { build(); }

  vector<ll> &operator[](int i) { return tree[i]; }
  int size() const { return tree.size(); }
  int id(int i) { return idar[i] == -1 ? idcc[i] : idar[i]; }
  bool is_arti(int i) { return idar[i] != -1; }
  int arti() const { return bcc.articulation.size(); }
};