#include <bits/stdc++.h>
using namespace std;
using ll = long long;

int main() {
  ios::sync_with_stdio(false);
  cin.tie(0);
  ll n;
  string s;
  cin >> n >> s;
  vector<string> v(n);
  for(auto &i : v) { cin >> i; }
  vector<ll> pre(n), suf(n);
  auto f = [&](string t) {
    ll p = 0, sz = ssize(t);
    for(ll i = 0; i < sz; i++) {
      if(t[i] == s[p]) { p++; }
      if(p == ssize(s)) { break; }
    }
    return p;
  };
  for(ll i = 0; i < n; i++) {
    pre[i] = f(v[i]);
    ranges::reverse(v[i]);
  }
  ranges::reverse(s);
  for(ll i = 0; i < n; i++) { suf[i] = f(v[i]); }
  ranges::sort(suf);
  ll r = 0;
  for(ll i = 0; i < n; i++) {
    r += suf.end() - ranges::lower_bound(suf, ssize(s) - pre[i]);
  }
  cout << r << "\n";
}
