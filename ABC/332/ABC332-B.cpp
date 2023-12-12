#include <bits/stdc++.h>
using namespace std;
using ll = long long;

int main() {
  ios::sync_with_stdio(false);
  cin.tie(0);

  ll N, G, M;
  cin >> N >> G >> M;

  ll g = 0, m = 0;
  while(N--) {
    if(g == G) { g = 0; }
    else if(m == 0) { m = M; }
    else {
      ll l = G - g;
      if(l <= m) {
        g = G;
        m -= l;
      }
      else {
        g += m;
        m = 0;
      }
    }
  }

  cout << g << " " << m << "\n";
}
