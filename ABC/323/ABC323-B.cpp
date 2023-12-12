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
  vector<ll> c(n);
  for(ll i = 0; i < n; i++) {
    for(ll j = 0; j < n; j++) {
      if(v[i][j] == 'o') { c[i]++; }
    }
  }
  vector<ll> idx(n);
  iota(idx.begin(), idx.end(), 0);
  ranges::sort(idx, [&](auto i, auto j) { if(c[i] != c[j]) { return c[i] > c[j]; } else { return i < j; } });
  for(auto &i : idx) { cout << i + 1 << " "; }
}
