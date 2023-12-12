#include <bits/stdc++.h>
using namespace std;
using ll = long long;

int main() {
  ios::sync_with_stdio(false);
  cin.tie(0);

  ll n, l, r;
  cin >> n >> l >> r;
  vector<ll> v(n);
  for(auto &i : v) { cin >> i; }

  for(auto &i : v) {
    if(i < l) { cout << l << " "; }
    else if(i > r) { cout << r << " "; }
    else { cout << i << " "; }
  }
}
