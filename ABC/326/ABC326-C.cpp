#include <bits/stdc++.h>
using namespace std;
using ll = long long;

int main() {
  ios::sync_with_stdio(false);
  cin.tie(0);
  ll n, m;
  cin >> n >> m;
  vector<ll> v(n);
  for(auto &i : v) { cin >> i; }
  ranges::sort(v);
  ll r = 0;
  for(ll i = 0; i < n; i++) {
    ll t = v[i] + m;
    ll p = ranges::lower_bound(v, t) - v.begin();
    r = max(r, p - i);
  }
  cout << r << "\n";
}
