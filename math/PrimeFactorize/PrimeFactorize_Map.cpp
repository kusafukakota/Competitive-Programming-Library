map<ll, ll> PriMap(ll n) {
  map<ll, ll> r;
  for(ll i = 2; i * i <= n; i++) {
    while(n % i == 0) { r[i]++, n /= i; }
  }
  if(n != 1) { r[n] = 1; }
  return r;
}
