#pragma once

#include <lib/Trie.hpp>

template<size_t X = 26, char margin = 'a'> struct AhoCorasick : Trie<X + 1, margin> {
  using TRIE = Trie<X + 1, margin>;
  using TRIE::c;
  using TRIE::next;
  using TRIE::st;
  using TRIE::TRIE;
  vector<int> cnt;
  void build(bool heavy = false) {
    int n = st.size();
    cnt.resize(n);
    for(int i = 0; i < n; i++) {
      if(heavy) { ranges::sort(st[i].idxs); }
      cnt[i] = st[i].idxs.size();
    }
    queue<int> q;
    for(int i = 0; i < (int)X; i++) {
      if(~next(0, i)) {
        next(next(0, i), X) = 0;
        q.emplace(next(0, i));
      }
      else { next(0, i) = 0; }
    }
    while(!q.empty()) {
      auto &x = st[q.front()];
      int fail = x.nxt[X];
      cnt[q.front()] += cnt[fail];
      q.pop();
      for(int i = 0; i < (int)X; i++) {
        int &nx = x.nxt[i];
        if(nx < 0) {
          nx = next(fail, i);
          continue;
        }
        q.emplace(nx);
        next(nx, X) = next(fail, i);
        if(heavy) {
          auto &idx = st[nx].idxs, &idy = st[next(fail, i)].idxs;
          vector<int> idz;
          ranges::set_union(idx, idy, back_inserter(idz));
          idx = idz;
        }
      }
    }
  }
  ll match_count(string s) {
    int res = 0, pos = 0;
    for(auto &c : s) {
      pos = next(pos, c - margin);
      res += cnt[pos];
    }
    return res;
  }
  vector<vector<int>> match(string s) {
    vector<vector<int>> res(c);
    int pos = 0;
    for(int i = 0; i < (int)s.size(); i++) {
      pos = next(pos, s[i] - margin);
      for(auto &x : st[pos].idxs) { res[x].emplace_back(i); }
    }
    return res;
  }
  int count(int pos) { return cnt[pos]; }
};