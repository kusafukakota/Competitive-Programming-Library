vector<ll> Base(ll x, ll n, bool re = false) {
  vector<ll> r;
  while(x != 0) {
    r.emplace_back(x % n);
    (x -= (x % n)) /= n;
  }
  if(re) {ranges::reverse(r);}
  return r;
}
