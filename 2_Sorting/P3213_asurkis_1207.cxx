#include <iostream>

using namespace std;

struct Point {
  long long x;
  long long y;
  int id;
};

bool operator<(const Point &a, const Point &b) { return a.x * b.y < a.y * b.x; }

template <typename T> void quick_sort(T begin, T end) {
  if (begin == end)
    return;
  T equal_left = begin;
  T equal = begin;
  T iter = begin;
  for (++iter; iter != end; ++iter) {
    if (!(*equal < *iter)) {
      swap(*++equal, *iter);
      if (*equal < *equal_left) {
        swap(*equal, *equal_left);
        ++equal_left;
      }
    }
  }
  quick_sort(begin, equal_left);
  if (equal != end) {
    quick_sort(++equal, end);
  }
}

int N;
Point points[10000];

int main() {
  cin >> N;
  for (int i = 0; i < N; ++i) {
    points[i].id = i + 1;
    cin >> points[i].x >> points[i].y;
  }

  int pivot = 0;
  for (int i = 1; i < N; ++i) {
    if (points[i].x < points[pivot].x)
      pivot = i;
  }

  swap(points[0], points[pivot]);
  for (int i = 1; i < N; ++i) {
    points[i].x -= points[0].x;
    points[i].y -= points[0].y;
  }

  quick_sort(points + 1, points + N);
  cout << points[0].id << ' ' << points[N / 2].id << endl;

  return 0;
}
