#include <bits/stdc++.h>
using namespace std;
using ll = long long;

int main() {
  ios::sync_with_stdio(false);
  cin.tie(0);

  ll M, D, y, m, d;
  cin >> M >> D >> y >> m >> d;
  if(D == d) {
    d = 1;
    if(M == m) {
      m = 1;
      y++;
    }
    else { m++; }
  }
  else { d++; }
  cout << y << " " << m << " " << d << "\n";
}
