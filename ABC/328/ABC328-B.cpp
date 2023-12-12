#include <bits/stdc++.h>
using namespace std;
using ll = long long;

int main() {
  ios::sync_with_stdio(false);
  cin.tie(0);
  ll n;
  cin >> n;
  vector<ll> v(n + 1, 0);
  for(ll i = 0; i < n; i++) { cin >> v[i + 1]; }
  ll r = 0;
  for(ll i = 1; i < 10; i++) {
    if(i > n) { break; }
    if(v[i] >= i) { r++; }
    if(v[i] >= i * 11) { r++; }
  }
  for(ll i = 11; i < 100; i += 11) {
    if(i > n) { break; }
    if(v[i] >= i / 11) { r++; }
    if(v[i] >= i) { r++; }
  }
  cout << r << "\n";
}
