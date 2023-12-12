#include <bits/stdc++.h>
using namespace std;
using ll = long long;

int main() {
  ios::sync_with_stdio(false);
  cin.tie(0);
  ll n, m;
  cin >> n >> m;
  vector<ll> v(m);
  for(auto &i : v) { cin >> i; }
  for(ll i = 1; i <= n; i++) {
    ll p = ranges::lower_bound(v, i) - v.begin();
    cout << v[p] - i << "\n";
  }
}
