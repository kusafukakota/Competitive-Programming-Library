#pragma once

ll DigSum(ll n) {
  ll r = 0;
  while(n) {
    r += n % 10;
    n /= 10;
  }
  return r;
}