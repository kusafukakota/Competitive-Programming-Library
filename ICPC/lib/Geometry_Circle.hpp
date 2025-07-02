#pragma once

#include <lib/Geometry_Segment.hpp>

struct Circle {
  Point p;
  Real r{};
  Circle() = default;
  Circle(const Point &p, const Real &r): p(p), r(r) {}
  friend istream &operator>>(istream &is, Circle &c) { return is >> c.p >> c.r; }
  friend ostream &operator<<(ostream &os, Circle &c) { return os << c.p << " ," << c.r; }
};
using Circles = vector<Circle>;

int contains(const Circle &c, const Point &p) { return sign(c.r - distance(c.p, p)) + 1; }  // 0:out, 1:on, 2:in
bool intersect(const Circle &c, const Point &p) { return eq(c.r, distance(c.p, p)); }
int intersect(const Circle &c, const Line &l) { return contains(c, projection(l, c.p)); }
int intersect(const Circle &c, const Segment &s) {
  int r = intersect(c, Line(s)), f = ccw(s.a, s.b, projection(s, c.p));
  if(r == 0) { return 0; }
  if(r == 1) { return f == 0 ? 1 : 0; }
  int f1 = sign(abs(c.p - s.a) - c.r), f2 = sign(abs(c.p - s.b) - c.r);
  if(f1 < 0 && f2 < 0) { return 0; }
  if(f1 < 0 || f2 < 0) { return 1; }
  if(f1 == 0 && f2 == 0) { return 2; }
  if(f1 == 0 || f2 == 0) { return f == 0 ? 2 : 1; }
  return f == 0 ? 2 : 0;
}
int intersect(const Circle &a, const Circle &b) {  // +2:外部 -2:内部 +1:外接 -1:内接 0:2点で交わる
  Real d = distance(a.p, b.p), R = a.r + b.r, r = fabs(a.r - b.r);
  if(sign(d - R) > 0) { return +2; }
  if(sign(d - r) < 0) { return -2; }
  if(eq(d, R)) { return +1; }
  if(eq(d, r)) { return -1; }
  return 0;
}
Points crosspoint(const Circle &c, const Line &l) {
  Point h = projection(l, c.p);
  if(intersect(c, l) == 0) { return {}; }
  if(intersect(c, l) == 1) { return {h}; }
  Point e = (l.b - l.a) / distance(l.a, l.b) * sqrt(norm(c.r) - norm(h - c.p));
  return {h + e, h - e};
}
Points crosspoint(const Circle &c, const Segment &s) {
  if(intersect(c, s) == 0) { return {}; }
  Points r = crosspoint(c, Line(s));
  if(intersect(c, s) == 2) { return r; }
  if(dot(s.a - r[0], s.b - r[0]) > 0) { swap(r[0], r[1]); }
  return {r[0]};
}
Points crosspoint(const Circle &l, const Circle &r) {
  const int i = intersect(l, r);
  if(abs(i) == 2) { return {}; }
  Real d = distance(l.p, r.p), t = acos((l.r * l.r - r.r * r.r + d * d) / (2 * l.r * d)), s = arg(r.p - l.p);
  Point e(l.r, 0), p = l.p + e.rotate(s + t), q = l.p + e.rotate(s - t);
  if(abs(i) == 1) { return {p}; }
  return {p, q};
}
Points tangent(const Circle &c, const Point &p) {
  const int i = contains(c, p);
  if(i == 2) { return {}; }
  if(i == 1) { return {p}; }
  return crosspoint(c, Circle(p, sqrt(norm(p - c.p) - c.r * c.r)));
}
Lines tangent(Circle &l, Circle &r) {
  Lines ret;
  if(sign(l.r - r.r) < 0) { swap(l, r); }
  Real g = norm(l.p - r.p);
  if(eq(g)) { return ret; }
  Point u = (r.p - l.p) / sqrt(g), v = u.rotate(PI * 0.5);
  for(int s : {-1, 1}) {
    Real h = (l.r + s * r.r) / sqrt(g);
    if(eq(1 - h * h)) { ret.emplace_back(Line(l.p + u * l.r, l.p + (u + v) * l.r)); }
    else if(sign(1 - h * h) > 0) {
      Point uu = u * h, vv = v * sqrt(1 - h * h);
      ret.emplace_back(Line(l.p + (uu + vv) * l.r, r.p - (uu + vv) * r.r * s));
      ret.emplace_back(Line(l.p + (uu - vv) * l.r, r.p - (uu - vv) * r.r * s));
    }
  }
  return ret;
}

Real Area(const Circle &c, const Polygon &P) {
  auto calc = [&](auto &&calc, const Point &a, const Point &b) -> Real {
    auto va = c.p - a, vb = c.p - b;
    Real f = cross(va, vb), ret = 0;
    if(eq(f)) { return ret; }
    if(max(abs(va), abs(vb)) < c.r + EPS) { return f; }
    if(distance(Segment(a, b), c.p) > c.r - EPS) {
      Point t(va.x * vb.x + va.y * vb.y, va.x * vb.y - va.y * vb.x);
      return norm(c.r) * arg(t);
    }
    auto u = crosspoint(c, Segment(a, b));
    if((int)u.size() == 1) { u.emplace_back(u[0]); }
    vector<Point> tot = {a, u[0], u[1], b};
    for(int i = 0; i < 3; i++) { ret += calc(calc, tot[i], tot[i + 1]); }
    return ret;
  };
  const int N = P.size();
  if(N < 3) { return 0; }
  Real A = 0;
  for(int i = 0; i < N; i++) { A += calc(calc, P[i], P[(i + 1) % N]); }
  return A * 0.5;
}