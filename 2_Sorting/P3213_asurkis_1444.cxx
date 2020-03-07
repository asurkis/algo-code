#define _USE_MATH_DEFINES
#include <cmath>
#include <iostream>

using namespace std;

struct Point {
  int id;
  int x;
  int y;
};

bool operator<(const Point &a, const Point &b) {
  double atan_a = atan2(a.y, a.x);
  double atan_b = atan2(b.y, b.x);
  if (atan_a < atan_b)
    return true;
  if (atan_a > atan_b)
    return false;
  return a.x * a.x + a.y * a.y < b.x * b.x + b.y * b.y;
}

void merge_sort(Point *src, Point *dst, int size) {
  if (size < 2)
    return;
  int m = size / 2;
  merge_sort(dst, src, m);
  merge_sort(dst + m, src + m, size - m);

  for (int i = 0; i + i < size - m; ++i)
    swap(src[m + i], src[size - i - 1]);

  int l = 0;
  int r = size - 1;
  for (int i = 0; i < size; ++i)
    dst[i] = src[src[r] < src[l] ? r-- : l++];
}

int N;
Point points[30000];
Point buffer[30000];

int main() {
  cin >> N;
  for (int i = 0; i < N; ++i) {
    points[i].id = i + 1;
    cin >> points[i].x >> points[i].y;
  }

  for (int i = 1; i < N; ++i) {
    points[i].x -= points[0].x;
    points[i].y -= points[0].y;
  }

  for (int i = 0; i < N; ++i)
    buffer[i] = points[i];

  merge_sort(buffer + 1, points + 1, N - 1);

  int gap_index = 0;
  for (int i = 1; i < N; ++i) {
    int j = i % (N - 1) + 1;
    double atan_i = atan2(points[i].y, points[i].x);
    double atan_j = atan2(points[j].y, points[j].x);
    while (atan_j < atan_i)
      atan_j += 2 * M_PI;
    if (atan_j - atan_i >= M_PI) {
      gap_index = i;
      break;
    }
  }

  cout << N << endl;
  cout << points[0].id << endl;
  for (int i = 1; i < N; ++i)
    cout << points[(gap_index + i - 1) % (N - 1) + 1].id << endl;

  return 0;
}
