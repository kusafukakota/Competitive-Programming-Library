#pragma once

// return : gcd(a,b), {x,y} -> soltion of ax + by = gcd(a,b)
template<typename T> T ExtGcd(T a, T b, T &x, T &y) {
  T g = a;
  if(b != 0) {
    g = ExtGcd(b, a % b, y, x);
    y -= (a / b) * x;
  }
  else { x = 1, y = 0; }
  return g;
}