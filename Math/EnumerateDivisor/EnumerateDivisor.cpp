vector<ll> Div(ll n) {
  vector<ll> r;
  for(ll i = 1; i * i <= n; i++) {
    if(n % i == 0) {
      r.emplace_back(i);
      if(i * i != n) { r.emplace_back(n / i); }
    }
  }
  ranges::sort(r);
  return r;
}
