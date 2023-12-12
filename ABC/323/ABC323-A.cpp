#include <bits/stdc++.h>
using namespace std;
using ll = long long;

int main() {
  ios::sync_with_stdio(false);
  cin.tie(0);
  string s;
  cin >> s;
  for(ll i = 1; i < 16; i += 2) {
    if(s[i] == '1') {
      cout << "No\n";
      return 0;
    }
  }
  cout << "Yes\n";
}
