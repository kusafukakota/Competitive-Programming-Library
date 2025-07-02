#pragma once

#include <lib/Geometry_Point.hpp>

struct Line {
  Point a, b;
  Line() = default;
  Line(const Point &a, const Point &b): a(a), b(b) {}
  Line(const Real &A, const Real &B, const Real &C) {  // Ax + By = C
    if(eq(A)) {
      assert(!eq(B));
      a = Point(0, C / B), b = Point(1, C / B);
    }
    else if(eq(B)) { a = Point(C / A, 0), b = Point(C / A, 1); }
    else if(eq(C)) { a = Point(0, C / B), b = Point(1, (C - A) / B); }
    else { a = Point(0, C / B), b = Point(C / A, 0); }
  }
  friend istream &operator>>(istream &is, Line &l) { return is >> l.a >> l.b; }
  friend ostream &operator<<(ostream &os, const Line &l) { return os << l.a << " to " << l.b; }
};
using Lines = vector<Line>;

bool parallel(const Line &l, const Line &r) { return eq(cross(l.b - l.a, r.b - r.a)); }
bool orthogonal(const Line &l, const Line &r) { return eq(dot(l.a - l.b, r.a - r.b)); }
Point projection(const Line &l, const Point &p) { return l.a + (l.a - l.b) * (dot(p - l.a, l.a - l.b) / norm(l.a - l.b)); }
Point reflection(const Line &l, const Point &p) { return projection(l, p) * 2 - p; }
bool intersect(const Line &l, const Point &p) { return abs(ccw(l.a, l.b, p)) != 1; }
int intersect(const Line &l, const Line &r) { return parallel(l, r) ? intersect(l, r.a) ? 2 : 0 : 1; }  // 0:parallel, 1:intersect 2:l=r
Real distance(const Line &l, const Point &p) { return distance(p, projection(l, p)); }
Real distance(const Line &l, const Line &r) { return intersect(l, r) ? 0 : distance(l, r.a); }
Point crosspoint(const Line &l, const Line &r) {
  Real A = cross(l.b - l.a, r.b - r.a), B = cross(l.b - l.a, l.b - r.a);
  return eq(A) && eq(B) ? r.a : r.a + (r.b - r.a) * B / A;
}
Line PerpendicularBisector(const Point &l, const Point &r) {
  Point m = (l + r) * 0.5, d = r - l;
  Point p(m.x - d.y, m.y + d.x);
  return Line(m, p);
}
Point Circumcenter(const Point &a, const Point &b, const Point &c) { return crosspoint(PerpendicularBisector(a, b), PerpendicularBisector(a, c)); }

Polygon ConvexCut(const Polygon &P, const Line &l) {
  const int N = P.size();
  Polygon r;
  for(int i = 0; i < N; i++) {
    const Point &now = P[i], &nxt = P[(i + 1) % N];
    Real cf = cross(l.a - now, l.b - now), cs = cross(l.a - nxt, l.b - nxt);
    if(sign(cf) >= 0) { r.emplace_back(now); }
    if(sign(cf) * sign(cs) < 0) { r.emplace_back(crosspoint(Line(now, nxt), l)); }
  }
  return r;
}