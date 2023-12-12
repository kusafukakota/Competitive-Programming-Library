#include <bits/stdc++.h>
using namespace std;
using ll = long long;

int main() {
  ios::sync_with_stdio(false);
  cin.tie(0);
  ll n;
  string s;
  cin >> n >> s;
  ll sz = ssize(s);
  vector<string> v(n);
  vector<ll> r;
  for(auto &i : v) { cin >> i; }
  for(ll i = 0; i < n; i++) {
    string t = v[i];
    if(abs(ssize(v[i]) - sz) >= 2) { continue; }
    if(ssize(v[i]) == sz) {
      ll c = 0;
      for(ll j = 0; j < sz; j++) {
        if(v[i][j] != s[j]) { c++; }
      }
      if(c <= 1) { r.emplace_back(i + 1); }
    }
    else {
      string S = s;
      while(ssize(S) && ssize(t)) {
        if(t.back() == S.back()) {
          t.pop_back();
          S.pop_back();
        }
        else { break; }
      }
      ranges::reverse(t);
      ranges::reverse(S);
      while(ssize(S) && ssize(t)) {
        if(t.back() == S.back()) {
          t.pop_back();
          S.pop_back();
        }
        else { break; }
      }
      if(ssize(S) == 0 || ssize(t) == 0) { r.emplace_back(i + 1); }
    }
  }
  ranges::sort(r);
  cout << ssize(r) << "\n";
  for(auto &i : r) { cout << i << " "; }
}
