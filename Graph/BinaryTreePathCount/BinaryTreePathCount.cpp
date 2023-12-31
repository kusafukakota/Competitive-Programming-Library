vector<mint> BinaryTreePathCount(ll n) {
  ll D = 63 - __builtin_clzll(n + 1), L = n - (1LL << D) + 1;
  vector<mint> cnt(130), bin(130, 1);
  for(ll i = 1; i < 130; i++) { bin[i] = bin[i] * 2; }
  map<ll, mint> memo[65][130];
  for(ll k = 0; k < 130; k++) {
    auto calc = [&](auto &&calc, ll d, ll l) -> mint {
      if(!d) { return 0; }
      if(memo[d][k].contains(l)) { return memo[d][k][l]; }
      mint r = 0;
      if(k < d) {
        r = bin[k];
        if(k >= 2) { r += bin[k - 2] * (k - 1); }
      }
      else if(k >= 2) { r += bin[k - 2] * max(0LL, d * 2 - k - 1); }
      ll t = 1LL << d - 1;
      if(l >= t) {
        r += calc(calc, d, 0) + calc(calc, d - 1, l - t);
        if(k == d) { r += l; }
        else if(k > d && k < d * 2) { r += l * bin[k - d - 1]; }
        else if(k == d * 2) { r += mint(t) * (l - t); }
      }
      else {
        r += calc(calc, d - 1, l) + calc(calc, d - 1, 0);
        if(k == d) { r += l; }
        else if(k > d && k < d * 2) { r += l * bin[k - d - 1]; }
      }
      return memo[d][k][l] = r;
    };
    cnt[k] = calc(calc, D, L);
  }
  return cnt;
}
