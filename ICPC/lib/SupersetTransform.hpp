#pragma once

struct SupersetTransform {
  template<typename T> static void ZetaTransform(vector<T> &v) {
    const int n = v.size();
    for(int i = 1; i < n; i <<= 1) {
      for(int j = 0; j < n; j += i << 1) {
        for(int k = 0; k < i; k++) { v[j + k] += v[j + k + i]; }
      }
    }
  }
  template<typename T> static void MobiusTransform(vector<T> &v) {
    const int n = v.size();
    for(int i = 1; i < n; i <<= 1) {
      for(int j = 0; j < n; j += i << 1) {
        for(int k = 0; k < i; k++) { v[j + k] -= v[j + k + i]; }
      }
    }
  }
};