#pragma once

template<typename T, bool get_min = true> pair<ll, T> GoldenSectionSearch(const auto &f, ll Min, ll Max) {
  assert(Min <= Max);
  ll a = Min - 1, x, b, s = 1, t = 2;
  while(t < Max - Min + 2) { swap(s += t, t); }
  x = a + t - s;
  b = a + t;
  T fx = f(x), fy;
  while(a + b != 2 * x) {
    ll y = a + b - x;
    if(Max < y || (fy = f(y), get_min ? fx < fy : fx > fy)) {
      b = a;
      a = y;
    }
    else {
      a = x;
      x = y;
      fx = fy;
    }
  }
  return {x, f(x)};
}