#include <bits/stdc++.h>
using namespace std;
using ll = long long;

int main() {
  ios::sync_with_stdio(false);
  cin.tie(0);
  string s;
  cin >> s;
  ll n = ssize(s);
  vector<char> v;
  for(ll i = 0; i < n; i++) {
    v.emplace_back(s[i]);
    ll sz = ssize(v);
    if(sz < 3) { continue; }
    if(v[sz - 3] == 'A' && v[sz - 2] == 'B' && v[sz - 1] == 'C') {
      for(ll j = 0; j < 3; j++) { v.pop_back(); }
    }
  }
  for(auto &i : v) { cout << i; }
}
