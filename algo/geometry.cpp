#include <bits/stdc++.h>
using namespace std;

mt19937 rnd(228);
// rnd() use

const int INF = 1e9;

typedef long double ld;

struct PT {
  ld x, y;

  PT operator+(const PT &p) { return {x + p.x, y + p.y}; }
  PT operator-(const PT &p) { return {x - p.x, y - p.y}; }
  PT operator*(ld c) { return {x * c, y * c}; }
  PT operator/(ld c) { return {x / c, y / c}; }
  PT operator+=(const PT &NV) {
    x += NV.x, y += NV.y; return *this;
  }

  void rotate(ld angle) {
    ld nx = cos(angle) * x - sin(angle) * y;
    ld ny = sin(angle) * x + cos(angle) * y;
    x = nx, y = ny;
  }

};

ld dot(PT p, PT q) { return p.x * q.x + p.y * q.y; }
ld dis2(PT p, PT q) { return dot(p - q, p - q); }
ld cross(PT p, PT q) { return p.x * q.y - p.y * q.x; }

// SORTING https://codeforces.com/problemset/problem/598/C

bool up(PT p) { return p.y > 0 || (p.y == 0 && p.x >= 0); }

bool cmp_polar_sort(PT a, PT b) {
  return up(a) == up(b) ? cross(a,b) > 0 : up(a) > up(b);
  // in the beggining vectors with y>=0, than others. Sorted counterclockwise
}

bool angleLess(PT p1, PT p2, PT q1, PT q2) {
  PT p = {dot(p1,p2), abs(cross(p1,p2))};
  PT q = {dot(q1,q2), abs(cross(q1,q2))};
  return cmp_polar_sort(p,q);
}

PT p[N];

PT rotate(PT p, PT q, ld alpha) {
  p = p - q;
  p.rotate(alpha);
  return q + p;
}

ld area(PT p, PT q, PT r) {
  return abs(cross(q - p, r - p)) / 2;
}

struct Line {
  int a, b, c;

  void build(PT p1, PT p2) {
    a = p1.y - p2.y, b = p2.x - p1.x, c = p1.x * p2.y - p1.y * p2.x;
  }

  bool onLine(PT p) {
    return a * p.x + b * p.y + c == 0;
  }
};

// 3 points!!!
// http://algolist.ru/maths/geom/equation/circle.php
