#include <bits/stdc++.h>
using namespace std;
using ll = long long;

int main() {
  ios::sync_with_stdio(false);
  cin.tie(0);
  ll n;
  cin >> n;
  while(n % 2 == 0) { n /= 2; }
  while(n % 3 == 0) { n /= 3; }
  cout << (n == 1 ? "Yes" : "No") << "\n";
}
