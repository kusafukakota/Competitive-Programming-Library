#include <bits/stdc++.h>
using namespace std;
using ll = long long;

struct RNG {
  mt19937_64 mt;
  RNG(): mt(chrono::steady_clock::now().time_since_epoch().count()) {}
  ll operator()(ll a, ll b) {
    uniform_int_distribution<ll> dist(a, b);
    return dist(mt);
  }
  ll operator()(ll b) { return (*this)(0, b); }
} rng;

ostream &operator<<(ostream &os, const vector<ll> &v) {
  for(auto i = v.begin(); i != v.end(); i++) {
    if(i != v.begin()) { os << " "; }
    os << *i;
  }
  return os;
}
ostream &operator<<(ostream &os, const vector<pair<ll, ll>> &v) {
  for(auto i = v.begin(); i != v.end(); i++) {
    if(i != v.begin()) { os << "\n"; }
    os << i->first << " " << i->second;
  }
  return os;
}

ll LL(ll l, ll r) {
  ll n = rng(l, r);
  cout << n << "\n";
  return n;
}
ll LL(ll r) { return LL(1, r); }

vector<ll> VI(ll n, ll l, ll r) {
  vector<ll> v(n);
  for(ll i = 0; i < n; i++) { v[i] = rng(l, r); }
  cout << v << "\n";
  return v;
}
vector<ll> VI(ll n, ll r) { return VI(n, 1, r); }
template<typename I> void shuffle(I l, I r) {
  if(l == r) { return; }
  int n = 1;
  for(auto it = l + 1; it != r; it++) {
    n++;
    ll j = rng(0, n - 1);
    if(j != n - 1) { iter_swap(it, l + j); }
  }
}
vector<ll> Perm(ll n, ll l = 1) {
  vector<ll> v(n);
  iota(v.begin(), v.end(), l);
  shuffle(v.begin(), v.end());
  cout << v << "\n";
  return v;
}
vector<ll> Choice(ll n, ll l, ll r) {
  assert(n <= r - l + 1);
  set<ll> s;
  while(s.size() < n) { s.insert(rng(l, r)); }
  vector<ll> v(s.begin(), s.end());
  cout << v << "\n";
  return v;
}

vector<pair<ll, ll>> VP(ll n, ll l1, ll r1, ll l2, ll r2) {
  vector<pair<ll, ll>> v(n);
  for(ll i = 0; i < n; i++) { v[i] = {rng(l1, r1), rng(l2, r2)}; }
  cout << v << "\n";
  return v;
}
vector<pair<ll, ll>> VP(ll n, ll r1, ll r2) { return VP(n, 1, r1, 1, r2); }
vector<pair<ll, ll>> VP(ll n, ll r) { return VP(n, 1, r, 1, r); }

string STR(ll n, char l = 'a', char r = 'z') {
  string s = "";
  ll c = r - l;
  for(ll i = 0; i < n; i++) { s += (l + rng(0, c)); }
  cout << s << "\n";
  return s;
}

vector<vector<ll>> VVI(ll h, ll w, ll l, ll r) {
  vector<vector<ll>> v;
  for(ll i = 0; i < h; i++) { v.emplace_back(VI(w, l, r)); }
  return v;
}
vector<vector<ll>> VVI(ll h, ll w, ll r) {
  return VVI(h, w, 1, r);
}
vector<vector<ll>> VVI(ll n, ll r) {
  return VVI(n, n, 1, r);
}

struct Edge {
  int u, v;
  ll w;
  int idx;
  Edge(int _u, int _v, ll _w = 1, int _idx = -1): u(_u), v(_v), w(_w), idx(_idx) {}
};
struct Graph {
  int n, m;
  vector<Edge> es;
  bool weighted;

  Graph(int _n = 0, bool _weighted = false): n(_n), m(0), weighted(_weighted) {}
  int edges_size() const { return m; }

  void add_directed_edge(int u, int v, ll w = 1, int idx = -1) {
    es.emplace_back(u, v, w, idx);
    m++;
  }

  void add_undirected_edge(int u, int v, ll w = 1, int idx = -1) {
    int mn = min(u, v), mx = max(u, v);
    add_directed_edge(mn, mx, w, idx);
  }

  vector<vector<Edge>> adjacent_list(bool directed = false) const {
    vector<vector<Edge>> g(n);
    for(auto &[u, v, w, i] : es) {
      g[u].emplace_back(u, v, w, i);
      if(!directed) { g[v].emplace_back(v, u, w, i); }
    }
    return g;
  }

  vector<vector<ll>> adjacent_matrix(bool directed = false) const {
    vector<vector<ll>> g(n, vector<ll>(n, 0));
    for(auto &[u, v, w, _] : es) {
      g[u][v] = w;
      if(!directed) { g[v][u] = w; }
    }
    return g;
  }

  void print_matrix(ostream &os, bool directed = false) const {
    auto g = adjacent_matrix(directed);
    for(int i = 0; i < n; i++) {
      for(int j = 0; j < n; j++) {
        os << g[i][j] << " \n"[j == n - 1];
      }
    }
  }

  void print_edge(ostream &os, bool origin_0 = false) const {
    for(auto &e : es) {
      os << e.u + (origin_0 ? 0 : 1);
      os << " " << e.v + (origin_0 ? 0 : 1);
      if(weighted) { os << " " << e.w; }
      os << "\n";
    }
  }

  void print(ostream &os, bool origin_0 = false) const {
    cout << n << " " << m << "\n";
    print_edge(os, origin_0);
  }

  friend ostream &operator<<(ostream &os, const Graph &g) {
    g.print_edge(os);
    return os;
  }
};


struct UndirectedGraphGenerator {
 private:
  ll _w_min, _w_max;
  void set_weight(bool weighted, ll w_min, ll w_max) {
    _w_min = w_min, _w_max = w_max;
    if(!weighted) _w_min = _w_max = 1;
  }
  void add_edge(Graph &g, int i, int j) {
    ll w = _w_min == _w_max ? _w_min : rng(_w_min, _w_max);
    g.add_undirected_edge(i, j, w);
  }

 public:
  UndirectedGraphGenerator(): _w_min(1), _w_max(1) {}

  /**
   * ランダムケース生成用。
   *  条件を満たす全ての関数の中からランダムに1つを選んでグラフを生成。
   */
  Graph GRAPH(int n, bool is_tree = false, bool weighted = false, ll w_min = 1, ll w_max = 1) {
    using F = Graph (UndirectedGraphGenerator::*)(int, bool, ll, ll, bool);
    vector<F> f{TREE, PATH, STAR, PERFECT, SIMPLE, NAMORI, SIMPLE_SPARSE};
    int mx = is_tree ? 2 : 6;
    return (this->*f[rng(0, mx)])(n, weighted, w_min, w_max, !is_tree);
  }

  // ランダムな無向の木を出力
  Graph TREE(int n, bool weighted = false, ll w_min = 1, ll w_max = 1, bool edgecount = false) {
    set_weight(weighted, w_min, w_max);
    Graph g(n, weighted);
    if(n == 2) { add_edge(g, 0, 1); }
    if(n <= 2) { return g; }
    vector<int> code(n - 2), deg(n, 1);
    for(auto &i : code) {
      i = rng(0, n - 1);
      deg[i]++;
    }
    set<int> js;
    for(int j = 0; j < n; j++) {
      if(deg[j] == 1) { js.insert(j); }
    }
    for(auto &i : code) {
      int j = *js.begin();
      add_edge(g, i, j);
      js.erase(begin(js));
      if(--deg[i] == 1) { js.insert(i); }
      deg[j]--;
    }
    int u = *js.begin(), v = *next(js.begin());
    add_edge(g, u, v);
    assert(g.edges_size() == n - 1);
    if(edgecount) { cout << g.m << "\n"; }
    cout << g << "\n";
    return g;
  }

  // ランダムな無向のパスグラフを出力
  Graph PATH(int n, bool weighted = false, ll w_min = 1, ll w_max = 1, bool edgecount = true) {
    set_weight(weighted, w_min, w_max);
    vector<int> ord(n);
    iota(ord.begin(), ord.end(), 0);
    shuffle(ord.begin(), ord.end());
    Graph g(n, weighted);
    for(int i = 0; i < n - 1; i++) { add_edge(g, ord[i], ord[i + 1]); }
    if(edgecount) { cout << g.m << "\n"; }
    cout << g << "\n";
    return g;
  }

  // ランダムな無向のスターグラフを出力
  Graph STAR(int n, bool weighted = false, ll w_min = 1, ll w_max = 1, bool edgecount = true) {
    set_weight(weighted, w_min, w_max);
    vector<int> ord(n);
    iota(ord.begin(), ord.end(), 0);
    shuffle(ord.begin(), ord.end());
    Graph g(n, weighted);
    for(int i = 1; i < n; i++) { add_edge(g, ord[0], ord[i]); }
    if(edgecount) { cout << g.m << "\n"; }
    cout << g << "\n";
    return g;
  }

  // 完全グラフ
  Graph PERFECT(int n, bool weighted = false, ll w_min = 1, ll w_max = 1, bool edgecount = true) {
    set_weight(weighted, w_min, w_max);
    Graph g(n, weighted);
    for(int i = 0; i < n; i++) {
      for(int j = i + 1; j < n; j++) { add_edge(g, i, j); }
    }
    if(edgecount) { cout << g.m << "\n"; }
    cout << g << "\n";
    return g;
  }

  // 単純グラフ
  Graph SIMPLE(int n, bool weighted = false, ll w_min = 1, ll w_max = 1, bool edgecount = true) {
    set_weight(weighted, w_min, w_max);
    Graph g(n, weighted);
    for(int i = 0; i < n; i++) {
      for(int j = i + 1; j < n; j++) {
        if(rng(0, 1) == 1) { add_edge(g, i, j); }
      }
    }
    if(edgecount) { cout << g.m << "\n"; }
    cout << g << "\n";
    return g;
  }

  // なもりグラフ
  Graph NAMORI(int n, bool weighted = false, ll w_min = 1, ll w_max = 1, bool edgecount = true) {
    set_weight(weighted, w_min, w_max);
    Graph g(n, weighted);
    for(int i = 0; i < n; i++) {
      if(!i) { add_edge(g, i, rng(1, n - 1)); }
      else { add_edge(g, i, rng(0, i - 1)); }
    }
    if(edgecount) { cout << g.m << "\n"; }
    cout << g << "\n";
    return g;
  }

  // 疎な単純グラフ
  Graph SIMPLE_SPARSE(int n, bool weighted = false, ll w_min = 1, ll w_max = 1, bool edgecount = true) {
    set_weight(weighted, w_min, w_max);
    if(n == 0) { return Graph{}; }
    int m = rng(0, n - 1);
    set<pair<int, int>> es;
    while((int)es.size() < m) {
      int i = rng(0, n - 1), j = rng(0, n - 1);
      if(i >= j) { continue; }
      es.emplace(i, j);
    }
    Graph g(n, weighted);
    for(auto &[i, j] : es) { add_edge(g, i, j); }
    if(edgecount) { cout << g.m << "\n"; }
    cout << g << "\n";
    return g;
  }
} G;

// 値の範囲は全て閉区間


int main() {
  ios::sync_with_stdio(false);
  cin.tie(nullptr);

}
