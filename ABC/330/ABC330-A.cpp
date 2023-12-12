#include <bits/stdc++.h>
using namespace std;
using ll = long long;

int main() {
  ios::sync_with_stdio(false);
  cin.tie(0);

  ll n, l;
  cin >> n >> l;
  vector<ll> v(n);
  for(auto &i : v) { cin >> i; }
  cout << ranges::count_if(v, [&](auto x) { return x >= l; }) << "\n";
}
