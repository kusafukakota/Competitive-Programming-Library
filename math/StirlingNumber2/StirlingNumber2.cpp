template<typename T> vector<vector<T>> StirlingTable(ll n) {
  vector<vector<T>> r(n + 1, vector<T>(n + 1, 0));
  r[0][0] = 1;
  for(ll i = 1; i <= n; i++) {
    for(ll j = 1; j <= i; j++) {
      r[i][j] = r[i - 1][j - 1] + r[i - 1][j] * j;
    }
  }
  return r;
}
