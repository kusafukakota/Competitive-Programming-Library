template<size_t X = 26, char margin = 'a'> struct Trie {
  struct Node {
    array<int, X> nxt;
    vector<int> idxs;
    int idx;
    char key;
    Node(char c): idx(-1), key(c) { ranges::fill(nxt, -1); }
  };
  vector<Node> st;
  Trie(char c = '$') { st.emplace_back(c); }
  inline int &next(int i, int j) { return st[i].nxt[j]; }
  void add(const string &s, int x) {
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

template<size_t X = 26, char margin = 'a'> struct AhoCorasick : Trie<X + 1, margin> {
  using TRIE = Trie<X + 1, margin>;
  using TRIE::next;
  using TRIE::st;
  using TRIE::TRIE;
  vector<int> cnt;
  void build(int heavy = true) {
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
          ranges::set_union(idx, idy.back_inserter(idz));
          idx = idz;
        }
      }
    }
  }
  vector<int> match(string s, int heavy = true) {
    vector<int> res(heavy ? TRIE::size() : 1);
    int pos = 0;
    for(auto &c : s) {
      pos = next(pos, c - margin);
      if(heavy) {
        for(auto &x : st[pos].idxs) { res[x]++; }
      }
      else { res[0] += cnt[pos]; }
    }
    return res;
  }
  int count(int pos) { return cnt[pos]; }
};
