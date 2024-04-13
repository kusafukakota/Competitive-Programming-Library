template<typename T> pair<vector<vector<int>>, int> CartesianTree(vector<T> &v) {
  int N = ssize(v);
  vector<vector<int>> g(N);
  vector<int> p(N, -1), st;
  st.reserve(N);
  for(int i = 0; i < N; i++) {
    int pre = -1;
    while(!st.empty() && v[i] < v[st.back()]) {
      pre = st.back();
      st.pop_back();
    }
    if(pre != -1) { p[pre] = i; }
    if(!st.empty()) { p[i] = st.back(); }
    st.emplace_back(i);
  }
  int root = -1;
  for(int i = 0; i < N; i++) {
    if(p[i] != -1) { g[p[i]].emplace_back(i); }
    else root = i;
  }
  return {g, root};
}
