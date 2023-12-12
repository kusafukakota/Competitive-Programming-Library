#include <bits/stdc++.h>
using namespace std;
using ll = long long;

int main() {
  ios::sync_with_stdio(false);
  cin.tie(0);
  ll x, y;
  cin >> x >> y;
  if(x < y) { cout << (y - x <= 2 ? "Yes" : "No") << "\n"; }
  else { cout << (x - y <= 3 ? "Yes" : "No") << "\n"; }
}
