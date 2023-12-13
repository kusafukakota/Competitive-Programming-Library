struct RNG {
  mt19937 mt;
  RNG(): mt(chrono::steady_clock::now().time_since_epoch().count()) {}
  int operator()(int a, int b) {
    uniform_int_distribution<int> dist(a, b);
    return dist(mt);
  }
  int operator()(int b) { return (*this)(0, b); }
} rng;
