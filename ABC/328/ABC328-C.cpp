#include <bits/stdc++.h>
using namespace std;
using ll = long long;

int main() {
  ios::sync_with_stdio(false);
  cin.tie(0);
  ll n, q;
  cin >> n >> q;
  string s;
  cin >> s;
  vector<ll> v(n - 1, 0);
  for(ll i = 0; i < n - 1; i++) {
    if(s[i] == s[i + 1]) { v[i]++; }
  }
  vector<ll> t(n, 0);
  for(ll i = 0; i < n - 1; i++) { t[i + 1] = t[i] + v[i]; }
  while(q--) {
    ll l, r;
    cin >> l >> r;
    l--, r--;
    cout << t[r] - t[l] << "\n";
  }
}
