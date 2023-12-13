vector<pair<ll, ll>> Prime(ll n) {
  vector<pair<ll, ll>> r;
  for(ll i = 2; i * i <= n; i++) {
    if(n % i != 0) { continue; }
    ll e = 0;
    while(n % i == 0) { e++, n /= i; }
    r.emplace_back(i, e);
  }
  if(n != 1) { r.emplace_back(n, 1); }
  return r;
}
