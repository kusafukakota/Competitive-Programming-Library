struct RangeUnionFind {
  vector<int> data, L, R;
  RangeUnionFind(int N): data(N, -1), L(N), R(N) {
    iota(L.begin(), L.end(), 0);
    iota(R.begin(), R.end(), 1);
  }
  int find(int k) { return data[k] < 0 ? k : data[k] = find(data[k]); }
  int unite(int x, int y) {
    if((x = find(x)) == (y = find(y))) { return false; }
    if(data[x] > data[y]) { swap(x, y); }
    data[x] += data[y];
    data[y] = x;
    L[x] = min(L[x], L[y]);
    R[x] = max(R[x], R[y]);
    return true;
  }
  void range_unite(int l, int r) {  // unite [l, r)
    if((l = max(l, 0)) >= (r = min(r, (int)data.size()))) { return; }
    int m;
    while((m = R[find(l)]) < r) { unite(l, m); }
  }
  int size(int k) { return -data[find(k)]; }
  int same(int x, int y) { return find(x) == find(y); }
};
