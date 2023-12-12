#include <bits/stdc++.h>
using namespace std;
using ll = long long;

int main() {
  ios::sync_with_stdio(false);
  cin.tie(0);

  ll N, M;
  string S;
  cin >> N >> M >> S;

  for(ll L = -1, R = 2000;;) {
    if(R - L <= 1) {
      cout << R << "\n";
      break;
    }
    ll Mid = (L + R) / 2;
    bool flag = true;
    ll a = M, b = Mid;
    for(auto &i : S) {
      if(i == '0') { a = M, b = Mid; }
      else if(i == '1') {
        if(a) { a--; }
        else if(b) { b--; }
        else {
          flag = false;
          break;
        }
      }
      else {
        if(b) { b--; }
        else {
          flag = false;
          break;
        }
      }
    }
    flag ? R = Mid : L = Mid;
  }
}
