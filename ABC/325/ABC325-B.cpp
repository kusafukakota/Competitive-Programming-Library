#include <bits/stdc++.h>
using namespace std;
using ll = long long;

int main() {
  ios::sync_with_stdio(false);
  cin.tie(0);
  ll n;
  cin >> n;
  vector<ll> a(n), b(n);
  for(ll i = 0; i < n; i++) { cin >> a[i] >> b[i]; }
  ll r = 0;
  for(ll i = 0; i < 24; i++) {
    ll tmp = 0;
    for(ll j = 0; j < n; j++) {
      ll t = (b[j] + i) % 24;
      if(t >= 9 && t <= 17) {
        tmp += a[j];
      }
    }
    r = max(r, tmp);
  }
  cout << r << "\n";
}
