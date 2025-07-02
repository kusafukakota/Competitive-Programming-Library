#pragma once

struct Lowlink {
 private:
  int dfs(int idx, int k, int par) {
    low[idx] = (ord[idx] = k++);
    int cnt = 0;
    bool arti = false, second = false;
    for(auto &to : g[idx]) {
      if(ord[to] == -1) {
        cnt++;
        k = dfs(to, k, idx);
        low[idx] = min(low[idx], low[to]);
        arti |= (par != -1) && (low[to] >= ord[idx]);
        if(ord[idx] < low[to]) { bridge.emplace_back(minmax<ll>(idx, to)); }
      }
      else if(to != par || second) { low[idx] = min(low[idx], ord[to]); }
      else { second = true; }
    }
    arti |= par == -1 && cnt > 1;
    if(arti) { articulation.emplace_back(idx); }
    return k;
  }

 public:
  const vector<vector<ll>> g;
  int N;
  vector<ll> ord, low;
  // 関節点
  vector<ll> articulation;
  // 橋 (辺(u, v)が u < v となるよう格納)
  vector<pair<ll, ll>> bridge;
  Lowlink(const vector<vector<ll>> &g_): g(g_), N(g.size()), ord(N, -1), low(N, -1) {
    for(int i = 0, k = 0; i < N; i++) {
      if(ord[i] == -1) { k = dfs(i, k, -1); }
    }
  }
};