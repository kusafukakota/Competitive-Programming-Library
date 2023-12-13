template<typename T> vector<vector<T>> Partition(ll n) {
  vector<vector<T>> r(n + 1, vector<T>(n + 1, 0));
  for(ll i = 0; i <= n; i++) { r[0][i] = 1; }
  for(ll i = 1; i <= n; i++) {
    for(ll j = 1; j <= n; j++) {
      r[i][j] = r[i][j - 1] + (i - j >= 0 ? r[i - j][j] : 0);
    }
  }
  return r;
}
