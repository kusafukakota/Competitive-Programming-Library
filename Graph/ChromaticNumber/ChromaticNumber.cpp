namespace ChromaticNumberImpl {
template<unsigned mod> int calc(int n, vector<pair<int, int>> hist) {
  for(int c = 1; c <= n; c++) {
    ll sm = 0;
    for(auto &[i, x] : hist) { sm += (x = ll(x) * i % mod); }
    if(sm % mod != 0) { return c; }
  }
  return n;
}
}  // namespace ChromaticNumberImpl

int ChromaticNumber(vector<vector<ll>> &g) {
  int n = g.size();
  vector<int> adj(n), dp(1 << n);
  for(int i = 0; i < n; i++) {
    for(auto &j : g[i]) {
      adj[i] |= 1 << j;
      adj[j] |= 1 << i;
    }
  }
  dp[0] = 1;
  for(int i = 1; i < 1 << n; i++) {
    int j = __builtin_ctz(i), k = i & (i - 1);
    dp[i] = dp[k] + dp[k & ~adj[j]];
  }
  vector<int> memo((1 << n) + 1);
  for(int i = 0; i < (1 << n); i++) { memo[dp[i]] += __builtin_parity(i) ? -1 : 1; }
  vector<pair<int, int>> hist;
  for(int i = 1; i <= (1 << n); i++) {
    if(memo[i]) { hist.emplace_back(i, memo[i]); }
  }
  return min(ChromaticNumberImpl::calc<1000000021>(n, hist), ChromaticNumberImpl::calc<1000000033>(n, hist));
}
