#include <bits/stdc++.h>
using namespace std;
using ll = long long;

int main() {
  ios::sync_with_stdio(false);
  cin.tie(0);

  ll n;
  cin >> n;
  vector<ll> a(n);
  for(auto &i : a) { cin >> i; }
  auto b = a;
  ranges::sort(b);
  vector<ll> s(n + 1, 0);
  for(ll i = 0; i < n; i++) { s[i + 1] = s[i] + b[i]; }
  for(ll i = 0; i < n; i++) {
    ll idx = ranges::upper_bound(b, a[i]) - b.begin();
    cout << s.back() - s[idx] << " ";
  }
}
