#pragma once

#include <lib/PrimeEnum.hpp>

struct DivisorTransform {
  template<typename T> static void ZetaTransform(vector<T> &v) {
    const int n = v.size() - 1;
    for(auto &p : PrimeEnum(n)) {
      for(ll i = 1; i * p <= n; i++) { v[i * p] += v[i]; }
    }
  }
  template<typename T> static void MobiusTransform(vector<T> &v) {
    const int n = v.size() - 1;
    for(auto &p : PrimeEnum(n)) {
      for(ll i = n / p; i > 0; i--) { v[i * p] -= v[i]; }
    }
  }
  template<typename I, typename T> static void ZetaTransform(map<I, T> &m) {
    for(auto p = m.rbegin(); p != m.rend(); p++) {
      for(auto &x : m) {
        if(p->first == x.first) { break; }
        if(p->first % x.first == 0) { p->second += x.second; }
      }
    }
  }
  template<typename I, typename T> static void MobiusTransform(map<I, T> &m) {
    for(auto &x : m) {
      for(auto p = m.rbegin(); p != m.rend(); p++) {
        if(x.first == p->first) { break; }
        if(p->first % x.first == 0) { p->second -= x.second; }
      }
    }
  }
};