#include <bits/stdc++.h>
using namespace std;
using ll = long long;

int main() {
  ios::sync_with_stdio(false);
  cin.tie(0);
  map<ll, ll> m;
  for(ll i = 1; i <= 15; i++) {
    ll t = powl(i, i);
    m[t] = i;
  }
  ll n;
  cin >> n;
  if(!m.contains(n)) { cout << -1 << "\n"; }
  else cout << m[n] << "\n";
}
