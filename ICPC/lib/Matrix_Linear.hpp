#pragma once

#include <lib/Matrix.hpp>

Matrix<long double> rotate(const long double &theta) {
  Matrix<long double> r = {{cos(theta), -sin(theta)}, {sin(theta), cos(theta)}};
  return r;
}
Matrix<ll> rotate_left() {
  Matrix<ll> r = {{0, -1}, {1, 0}};
  return r;
}
Matrix<ll> rotate_right() {
  Matrix<ll> r = {{0, 1}, {-1, 0}};
  return r;
}
Matrix<ll> flip_x() {
  Matrix<ll> r = {{1, 0}, {0, -1}};
  return r;
}
Matrix<ll> flip_y() {
  Matrix<ll> r = {{-1, 0}, {0, 1}};
  return r;
}
Matrix<ll> flip_O() {
  Matrix<ll> r = {{-1, 0}, {0, -1}};
  return r;
}
Matrix<long double> flip_line(long double &theta) {
  theta *= 2;
  Matrix<long double> r = {{cos(theta), sin(theta)}, {sin(theta), -cos(theta)}};
  return r;
}