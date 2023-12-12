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
  ranges::sort(v);
  v.erase(unique(v.begin(), v.end()), v.end());
  ranges::reverse(v);
  cout << v[1] << "\n";
}
