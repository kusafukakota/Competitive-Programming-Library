#include <bits/stdc++.h>
using namespace std;
using ll = long long;

int main() {
  ios::sync_with_stdio(false);
  cin.tie(0);

  ll d;
  cin >> d;

  ll ans = 1e18;
  for(ll i = 0; i <= 1e6; i++) {
    ll t = d - i * i, s = (ll)sqrtl(t);
    for(ll j = s - 5; j <= s + 5; j++) {
      ans = min(ans, abs(j * j - t));
    }
  }
  cout << ans << "\n";
}
