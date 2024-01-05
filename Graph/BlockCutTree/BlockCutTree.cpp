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
        if(ord[idx] < low[to]) { bridge.emplace_back(minmax(idx, to)); }
      }
      else if(to != par || second) { low[idx] = min(low[idx], ord[to]); }
      else { second = true; }
    }
    arti |= par == -1 && cnt > 1;
    if(arti) { articulation.emplace_back(idx); }
    return k;
  }

 public:
  const vector<vector<int>> g;
  int N;
  vector<int> ord, low;
  vector<int> articulation;
  vector<pair<int, int>> bridge;
  Lowlink(const vector<vector<int>> &g_): g(g_), N(g.size()), ord(N, -1), low(N, -1) {
    for(int i = 0, k = 0; i < N; i++) {
      if(ord[i] == -1) { k = dfs(i, k, -1); }
    }
  }
};

struct BiConnectedComponents : Lowlink {
 private:
  void build() {
    used.assign(this->g.size(), 0);
    for(int i = 0; i < ssize(used); i++) {
      if(!used[i]) { dfs(i, -1); }
    }
  }
  void dfs(int idx, int par) {
    used[idx] = true;
    for(auto &to : this->g[idx]) {
      if(to == par) { continue; }
      if(!used[to] || this->ord[to] < this->ord[idx]) { tmp.emplace_back(minmax<int>(idx, to)); }
      if(!used[to]) {
        dfs(to, idx);
        if(this->low[to] >= this->ord[idx]) {
          bc.emplace_back();
          while(true) {
            auto e = tmp.back();
            bc.back().emplace_back(e);
            tmp.pop_back();
            if(e.first == min<int>(idx, to) && e.second == max<int>(idx, to)) { break; }
          }
        }
      }
    }
  }

 public:
  vector<int> used;
  vector<vector<pair<int, int>>> bc;
  vector<pair<int, int>> tmp;
  BiConnectedComponents(const vector<vector<int>> &g): Lowlink(g) { build(); }
};

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
  const vector<vector<int>> &g;
  BiConnectedComponents bcc;
  vector<vector<int>> tree;
  vector<int> idar, idcc;
  BlockCutTree(const vector<vector<int>> &g): g(g), bcc(g) { build(); }

  vector<int> &operator[](int i) { return tree[i]; }
  int size() const { return tree.size(); }
  int id(int i) { return idar[i] == -1 ? idcc[i] : idar[i]; }
  bool is_arti(int i) { return idar[i] != -1; }
  int arti() const { return bcc.articulation.size(); }
};
