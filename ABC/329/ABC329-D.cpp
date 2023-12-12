#include <bits/stdc++.h>
using namespace std;
using ll = long long;

int main() {
  ios::sync_with_stdio(false);
  cin.tie(0);

  ll n, m;
  cin >> n >> m;

  vector<ll> v(n, 0);
  set<pair<ll, ll>> s;
  for(ll i = 0; i < n; i++) { s.insert({0, -i}); }
  for(ll i = 0; i < m; i++) {
    ll x;
    cin >> x;
    x--;
    s.erase({v[x], -x});
    v[x]++;
    s.insert({v[x], -x});
    cout << -(*s.rbegin()).second + 1 << "\n";
  }
}
