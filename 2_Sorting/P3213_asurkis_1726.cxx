#include <algorithm>
#include <iostream>
#include <limits>
#include <string>
#include <utility>
#include <vector>

using namespace std;

template <typename T> struct Vec2 {
  T x, y;
  Vec2(const T &x, const T &y) : x(x), y(y) {}
};

template <typename T> Vec2<T> &operator+=(Vec2<T> &a, const Vec2<T> &b) {
  a.x += b.x;
  a.y += b.y;
  return a;
}

template <typename T> Vec2<T> operator+(const Vec2<T> &a, const Vec2<T> &b) {
  return Vec2(a) += b;
}

template <typename T> Vec2<T> &operator-=(Vec2<T> &a, const Vec2<T> &b) {
  a.x -= b.x;
  a.y -= b.y;
  return a;
}

template <typename T> Vec2<T> operator-(const Vec2<T> &a, const Vec2<T> &b) {
  return Vec2(a) -= b;
}

template <typename T> Vec2<T>& operator*=(Vec2<T>& a, const T& b) {
  a.x *= b;
  a.y *= b;
  return a;
}

template <typename T> Vec2<T> operator*(const Vec2<T>& a, const T& b) {
  return Vec2(a) *= b;
}

template <typename T> Vec2<T> operator*(const T& a, const Vec2<T>& b) {
  return Vec2(a) *= a;
}


int main() {
  int n;
  cin >> n;
  vector<Vec2<int> > xy(n);
  for (int i = 0; i < n; i++)
    cin >> xy[i].x >> xy[i].y;
  Vec2<int> sum(0, 0);
  for (int i = 0; i < n; i++)
    sum += xy[i];

  return 0;
}