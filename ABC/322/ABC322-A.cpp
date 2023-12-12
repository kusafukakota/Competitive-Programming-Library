#include <bits/stdc++.h>
using namespace std;
using ll = long long;

int main() {
  ios::sync_with_stdio(false);
  cin.tie(0);
  ll n;
  string s;
  cin >> n >> s;
  for(ll i = 0; i < n - 2; i++) {
    string t = s.substr(i, 3);
    if(t == "ABC") {
      cout << i + 1 << "\n";
      return 0;
    }
  }
  cout << -1 << "\n";
}
