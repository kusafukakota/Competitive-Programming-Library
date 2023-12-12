#include <bits/stdc++.h>
using namespace std;
using ll = long long;

int main() {
  ios::sync_with_stdio(false);
  cin.tie(0);
  ll n;
  cin >> n;
  vector<ll> v(n);
  for(auto &i : v) { cin >> i; }
  ll t = v[0];
  for(ll i = 0; i < n; i++) {
    if(v[i] != t) {
      cout << "No\n";
      return 0;
    }
  }
  cout << "Yes\n";
}
