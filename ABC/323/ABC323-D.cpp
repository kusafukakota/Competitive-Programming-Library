#include <bits/stdc++.h>
using namespace std;
using ll = long long;

int main() {
  ios::sync_with_stdio(false);
  cin.tie(0);
  ll n;
  cin >> n;
  vector<pair<ll, ll>> v(n);
  map<ll, ll> m;
  for(auto &[s, c] : v) {
    cin >> s >> c;
    m[s] = c;
  }
  auto it = m.begin();
  ll r = 0;
  while(it != m.end()) {
    auto [s, c] = *it;
    if(c >= 2) { m[s * 2] += c / 2; }
    r += c & 1;
    it++;
  }
  cout << r << "\n";
}
