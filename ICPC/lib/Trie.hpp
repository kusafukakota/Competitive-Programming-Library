#pragma once

template<size_t X = 26, char margin = 'a'> struct Trie {
  struct Node {
    array<int, X> nxt;
    vector<int> idxs;
    int idx;
    char key;
    Node(char c): idx(-1), key(c) { ranges::fill(nxt, -1); }
  };
  int c = 0;
  vector<Node> st;
  Trie() { st.emplace_back('$'); }
  Trie(const vector<string> &v) {
    st.emplace_back('$');
    for(auto &i : v) { insert(i); }
  }
  void clear() {
    st.clear();
    st.emplace_back('$');
  }
  inline int &next(int i, int j) { return st[i].nxt[j]; }
  void insert(const string &s) {
    int pos = 0;
    for(int i = 0; i < ssize(s); i++) {
      int k = s[i] - margin;
      if(~next(pos, k)) {
        pos = next(pos, k);
        continue;
      }
      int npos = st.size();
      next(pos, k) = npos;
      st.emplace_back(s[i]);
      pos = npos;
    }
    st[pos].idx = c;
    st[pos].idxs.emplace_back(c);
    c++;
  }
  int find(const string &s) {
    int pos = 0;
    for(int i = 0; i < ssize(s); i++) {
      int k = s[i] - margin;
      if(next(pos, k) < 0) { return -1; }
      pos = next(pos, k);
    }
    return pos;
  }
  int move(int pos, char c) {
    return pos < 0 ? -1 : next(pos, c - margin);
  }
  int size() const { return st.size(); }
  int idx(int pos) { return pos < 0 ? -1 : st[pos].idx; }
  vector<int> idxs(int pos) { return pos < 0 ? vector<int>() : st[pos].idxs; }
};
