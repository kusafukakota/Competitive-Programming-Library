#pragma once

vector<vector<ll>> Partition(int n, int Maxlen = -1, int Maxval = -1) {
  vector<vector<ll>> r;
  auto DFS = [&](auto &&DFS, vector<ll> &v, int sum) -> void {
    if(sum == n) {
      r.emplace_back(v);
      return;
    }
    if(Maxlen != -1 && ssize(v) == Maxlen) { return; }
    int nx = (ssize(v) ? v.back() : n);
    if(Maxval != -1) { nx = min(nx, Maxval); }
    nx = min(nx, n - sum);
    v.emplace_back(0);
    for(ll i = nx; i >= 1; i--) {
      v.back() = i;
      DFS(DFS, v, sum + i);
    }
    v.pop_back();
  };
  vector<ll> v;
  DFS(DFS, v, 0);
  return r;
}