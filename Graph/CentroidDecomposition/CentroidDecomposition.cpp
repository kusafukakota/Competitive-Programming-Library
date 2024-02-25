struct CentroidDecomposition {
 private:
  const vector<vector<ll>> &g;
  vector<int> sub;
  vector<bool> vis;
  vector<vector<int>> tree;
  int root;
  int get_size(int v, int p) {
    sub[v] = 1;
    for(auto &nv : g[v]) {
      if(nv == p || vis[nv]) { continue; }
      sub[v] += get_size(nv, v);
    }
    return sub[v];
  }
  int get_centroid(int v, int p, int mid) {
    for(auto &nv : g[v]) {
      if(nv == p || vis[nv]) { continue; }
      if(sub[nv] > mid) { return get_centroid(nv, v, mid); }
    }
    return v;
  }
  int dfs(int v) {
    int centroid = get_centroid(v, -1, get_size(v, -1) / 2);
    vis[centroid] = true;
    for(auto &nv : g[centroid]) {
      if(!vis[nv]) {
        int nxt = dfs(nv);
        if(centroid != nxt) { tree[centroid].emplace_back(nxt); }
      }
    }
    vis[centroid] = false;
    return centroid;
  }

 public:
  CentroidDecomposition(const vector<vector<ll>> &g): g(g), sub(g.size(), 0), vis(g.size(), false), tree(g.size()) {}
  int build() { return root = dfs(0); }
  inline vector<int> operator[](ll i) { return tree[i]; }
};
