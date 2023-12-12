#include <bits/stdc++.h>
using namespace std;
using ll = long long;

int main() {
  ios::sync_with_stdio(false);
  cin.tie(0);
  ll n;
  string s;
  cin >> n >> s;
  for(ll i = 0; i < n - 1; i++) {
    if(s[i] == 'a' && s[i + 1] == 'b') {
      cout << "Yes\n";
      return 0;
    }
    if(s[i] == 'b' && s[i + 1] == 'a') {
      cout << "Yes\n";
      return 0;
    }
  }
  cout << "No\n";
}
