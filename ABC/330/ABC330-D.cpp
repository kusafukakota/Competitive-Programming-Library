#include <bits/stdc++.h>
using namespace std;
using ll = long long;

int main() {
  ios::sync_with_stdio(false);
  cin.tie(0);

  ll n;
  cin >> n;
  vector<string> v(n);
  for(auto &i : v) { cin >> i; }

  vector<ll> cx(n, 0), cy(n, 0);
  for(ll i = 0; i < n; i++) {
    for(ll j = 0; j < n; j++) {
      if(v[i][j] == 'o') {
        cx[i]++;
        cy[j]++;
      }
    }
  }

  ll ans = 0;
  for(ll i = 0; i < n; i++) {
    for(ll j = 0; j < n; j++) {
      if(v[i][j] == 'x') { continue; }
      ans += (cx[i] - 1) * (cy[j] - 1);
    }
  }
  cout << ans << "\n";
}
