#pragma once

struct RNG {
  mt19937_64 mt;
  RNG(): mt(chrono::steady_clock::now().time_since_epoch().count()) {}
  ll operator()(ll a, ll b) {
    uniform_int_distribution<ll> dist(a, b);
    return dist(mt);
  }
  ll operator()(ll b) { return (*this)(0, b); }
  long double operator()() {
    uniform_real_distribution<long double> dist(0, 1);
    return dist(mt);
  }
} rng;