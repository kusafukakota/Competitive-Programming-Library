ll Divcnt(ll n, ll d) {
  ll r = 0;
  while(n % d == 0) { n /= d, r++; }
  return r;
}
