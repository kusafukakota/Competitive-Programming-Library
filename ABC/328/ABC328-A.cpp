#include <bits/stdc++.h>
using namespace std;
using ll = long long;

int main() {
  ios::sync_with_stdio(false);
  cin.tie(0);

  ll n, x;
  cin >> n >> x;
  vector<ll> v(n);
  ll r = 0;
  for(auto &i : v) {
    cin >> i;
    if(i <= x) { r += i; }
  }
  cout << r << "\n";
}
