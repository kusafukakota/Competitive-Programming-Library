#pragma once

template<typename T, bool get_min = true> pair<T, T> GoldenSectionSearch(const auto &f, T Min, T Max, T err = 1e-10) {
  assert(Min <= Max);
  const T phi = (1 + sqrt(T(5))) / 2;
  const int c = (log(Max - Min) - log(err)) / log(phi) + 1;
  T x = (phi * Min + Max) / (1 + phi), y = (Min + phi * Max) / (1 + phi);
  T fx = f(x), fy = f(y);
  for(int i = 0; i < c; i++) {
    if(get_min ^ (fx > fy)) {
      Max = y;
      y = x;
      fy = fx;
      x = (phi * Min + Max) / (1 + phi);
      fx = f(x);
    }
    else {
      Min = x;
      x = y;
      fx = fy;
      y = (Min + phi * Max) / (1 + phi);
      fy = f(y);
    }
  }
  return {x, f(x)};
}
