#pragma once

vector<ll> PhiTable(ll N) {
  vector<ll> phi(N + 1);
  iota(phi.begin(), phi.end(), 0);
  for(ll i = 2; i <= N; i++) {
    if(phi[i] == i) {
      for(ll j = i; j <= N; j += i) { phi[j] -= phi[j] / i; }
    }
  }
  return phi;
}