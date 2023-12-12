#include <bits/stdc++.h>
using namespace std;
using ll = long long;

int main() {
  ios::sync_with_stdio(false);
  cin.tie(0);
  ll n, m, p;
  cin >> n >> m >> p;
  vector<ll> a(n), b(m);
  for(auto &i : a) { cin >> i; }
  for(auto &i : b) { cin >> i; }
  ranges::sort(a);
  ranges::sort(b);
  vector<ll> sb(m + 1, 0);
  for(ll i = 0; i < m; i++) sb[i + 1] = sb[i] + b[i];
  ll r = 0;
  for(ll i = 0; i < n; i++) {
    ll l = ranges::lower_bound(b, p - a[i]) - b.begin();
    r += sb[l] + a[i] * l + p * (m - l);
  }
  cout << r << "\n";
}
