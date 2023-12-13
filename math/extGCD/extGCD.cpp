template<typename T> T extGCD(T a, T b, T &x, T &y) {
  T g = a;
  if(b != 0) {
    g = extGCD(b, a % b, y, x);
    y -= (a / b) * x;
  }
  else {x = 1, y = 0;}
  return g;
}
