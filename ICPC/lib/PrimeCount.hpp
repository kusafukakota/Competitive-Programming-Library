#pragma once

#include <lib/Root.hpp>

vector<bool> Eratosthenes(int n) {
  vector<bool> prime(n + 1, true);
  if(n >= 0) { prime[0] = false; }
  if(n >= 1) { prime[1] = false; }
  for(int i = 2; i * i <= n; i++) {
    if(!prime[i]) { continue; }
    for(int j = i + i; j <= n; j += i) { prime[j] = false; }
  }
  return prime;
}

struct PrimeCount {
 private:
  ll p2(ll x, ll y) {
    if(x < 4) { return 0; }
    ll a = cnt(y), b = cnt(Root(x));
    if(a >= b) { return 0; }
    ll sum = (a - 2) * (a + 1) / 2 - (b - 2) * (b + 1) / 2;
    for(ll i = a; i < b; i++) { sum += cnt(x / primes[i]); }
    return sum;
  }
  ll phi(ll m, ll n) {
    if(m < 1) { return 0; }
    if(n > m) { return 1; }
    if(n < 1) { return m; }
    if(m <= primes[n - 1] * primes[n - 1]) { return cnt(m) - n + 1; }
    if(m <= primes[n - 1] * primes[n - 1] * primes[n - 1] && m <= sq) {
      ll sx = cnt(Root(m)), ans = cnt(m) - (sx + n - 2) * (sx - n + 1) / 2;
      for(ll i = n; i < sx; i++) { ans += cnt(m / primes[i]); }
      return ans;
    }
    return phi(m, n - 1) - phi(m / primes[n - 1], n - 1);
  }

 public:
  ll sq;
  vector<bool> prime;
  vector<ll> prime_sum, primes;
  PrimeCount(ll n): sq(Root(n)), prime_sum(sq + 1) {
    prime = Eratosthenes(sq);
    for(int i = 1; i <= sq; i++) { prime_sum[i] = prime_sum[i - 1] + prime[i]; }
    primes.reserve(prime_sum[sq]);
    for(int i = 1; i <= sq; i++) {
      if(prime[i]) { primes.emplace_back(i); }
    }
  }
  ll cnt(ll n) {
    if(n <= sq) { return prime_sum[n]; }
    ll m = Root(n, 3), a = cnt(m);
    return phi(n, a) + a - 1 - p2(n, m);
  }
  inline ll operator()(ll n) { return cnt(n); }
} P(1e11);