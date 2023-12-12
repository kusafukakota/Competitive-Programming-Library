#include <bits/stdc++.h>
using namespace std;
using ll = long long;

int main() {
  ios::sync_with_stdio(false);
  cin.tie(0);
  ll n, x;
  cin >> n >> x;
  vector<ll> v(n - 1);
  for(auto &i : v) { cin >> i; }
  ll s = accumulate(v.begin(), v.end(), ll(0));
  auto f = [&](ll t) {
    auto u = v;
    u.emplace_back(t);
    ranges::sort(u);
    return s + t - u[0] - u.back();
  };
  for(ll i = 0; i <= 100; i++) {
    if(f(i) >= x) {
      cout << i << "\n";
      return 0;
    }
  }
  cout << -1 << "\n";
}
