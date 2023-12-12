#include <bits/stdc++.h>
using namespace std;
using ll = long long;

vector<pair<char, ll>> RLE(const string &s) {
  ll p = -1, n = s.size();
  vector<pair<char, ll>> r;
  for(ll i = 0; i < n - 1; i++) {
    if(s[i] != s[i + 1]) {
      r.emplace_back(s[i], i - p);
      p = i;
    }
  }
  r.emplace_back(s.back(), n - 1 - p);
  return r;
}

int main() {
  ios::sync_with_stdio(false);
  cin.tie(0);

  ll n;
  string s;
  cin >> n >> s;

  vector<ll> v(26, 0);
  for(auto &[c, l] : RLE(s)) {
    v[c - 'a'] = max(v[c - 'a'], l);
  }
  cout << accumulate(v.begin(), v.end(), ll(0)) << "\n";
}
