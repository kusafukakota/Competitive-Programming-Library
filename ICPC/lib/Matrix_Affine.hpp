#pragma once

#include <lib/Matrix.hpp>

template<typename T> Matrix<T> translation(const T &x, const T &y) {
  Matrix<T> r = {{1, 0, x}, {0, 1, y}, {0, 0, 1}};
  return r;
}
Matrix<long double> rotate(const long double &theta) {
  Matrix<long double> r = {{cos(theta), -sin(theta), 0}, {sin(theta), cos(theta), 0}, {0, 0, 1}};
  return r;
}
Matrix<ll> rotate_left() {
  Matrix<ll> r = {{0, -1, 0}, {1, 0, 0}, {0, 0, 1}};
  return r;
}
Matrix<ll> rotate_right() {
  Matrix<ll> r = {{0, 1, 0}, {-1, 0, 0}, {0, 0, 1}};
  return r;
}
Matrix<ll> flip_x() {
  Matrix<ll> r = {{1, 0, 0}, {0, -1, 0}, {0, 0, 1}};
  return r;
}
Matrix<ll> flip_y() {
  Matrix<ll> r = {{-1, 0, 0}, {0, 1, 0}, {0, 0, 1}};
  return r;
}
Matrix<ll> flip_O() {
  Matrix<ll> r = {{-1, 0, 0}, {0, -1, 0}, {0, 0, 1}};
  return r;
}