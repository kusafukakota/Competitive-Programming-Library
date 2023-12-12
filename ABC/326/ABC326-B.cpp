#include <bits/stdc++.h>
using namespace std;
using ll = long long;

int main() {
  ios::sync_with_stdio(false);
  cin.tie(0);
  vector<ll> v;
  for(ll i = 1; i < 10; i++) {
    for(ll j = 0; j < 10; j++) {
      if(i * j >= 10) { continue; }
      ll t = i * 100 + j * 10 + i * j;
      v.emplace_back(t);
    }
  }
  ranges::sort(v);
  ll n;
  cin >> n;
  for(auto &i : v) {
    if(i >= n) {
      cout << i << "\n";
      return 0;
    }
  }
}
