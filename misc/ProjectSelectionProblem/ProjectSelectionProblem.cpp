struct ProjectSelectionProblem {
  int N, S, G;
  ll offset;
  vector<tuple<int, int, ll>> e;
  ProjectSelectionProblem(int n): N(n + 2), S(n), G(n + 1), offset(0) {}
  void cost0(int i, ll c) { e.emplace_back(i, G, c); }
  void cost1(int i, ll c) { e.emplace_back(S, i, c); }
  void get0(int i, ll c) {
    offset += c;
    e.emplace_back(S, i, c);
  }
  void get1(int i, ll c) {
    offset += c;
    e.emplace_back(i, G, c);
  }
  void cost01(int i, int j, ll c) { e.emplace_back(i, j, c); }
  void cost10(int i, int j, ll c) { e.emplace_back(j, i, c); }
  void get00(int i, int j, ll c) {
    offset += c;
    e.emplace_back(S, N, c);
    e.emplace_back(N, i, 1e18);
    e.emplace_back(N, j, 1e18);
    N++;
  }
  void get11(int i, int j, ll c) {
    offset += c;
    e.emplace_back(N, G, c);
    e.emplace_back(i, N, 1e18);
    e.emplace_back(j, N, 1e18);
    N++;
  }
  template<typename T> void getall0(vector<T> &v, ll c) {
    offset += c;
    e.emplace_back(S, N, c);
    for(auto &i : v) { e.emplace_back(N, i, 1e18); }
    N++;
  }
  template<typename T> void getall1(vector<T> &v, ll c) {
    offset += c;
    e.emplace_back(N, G, c);
    for(auto &i : v) { e.emplace_back(i, N, 1e18); }
    N++;
  }
  ll build() {
    mf_graph<ll> g(N);
    for(auto &[s, t, c] : e) { g.add_edge(s, t, c); }
    return g.flow(S, G) - offset;
  }
};
