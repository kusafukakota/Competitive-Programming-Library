#include <bits/stdc++.h>
using namespace std;
using ll = long long;

int main() {
  ios::sync_with_stdio(false);
  cin.tie(0);
  string s;
  cin >> s;
  ll n = ssize(s);
  for(ll i = 0; i < n - 1; i++) {
    if(s[i] <= s[i + 1]) {
      cout << "No\n";
      return 0;
    }
  }
  cout << "Yes\n";
}
