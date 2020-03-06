#include <iostream>

using namespace std;

struct Point {
  int id;
  long long x;
  long long y;
};

bool operator<(const Point &a, const Point &b) { return a.x * b.y < a.y * b.x; }

void merge_sort(Point *src, Point *dst, int size) {
  if (size < 2)
    return;
  int m = size / 2;
  merge_sort(dst, src, m);
  merge_sort(dst + m, src + m, size - m);

  for (int i = 0; i + i < size - m; i++)
    swap(src[m + i], src[size - i - 1]);

  int l = 0;
  int r = size - 1;
  for (int i = 0; i < size; i++)
    dst[i] = src[src[r] < src[l] ? r-- : l++];
}

int N;
Point points[10000];
Point buffer[10000];

int main() {
  cin >> N;
  for (int i = 0; i < N; i++) {
    points[i].id = i + 1;
    cin >> points[i].x >> points[i].y;
  }

  int pivot = 0;
  for (int i = 1; i < N; i++) {
    if (points[i].x < points[pivot].x)
      pivot = i;
  }

  swap(points[0], points[pivot]);
  for (int i = 1; i < N; i++) {
    points[i].x -= points[0].x;
    points[i].y -= points[0].y;
  }

  for (int i = 0; i < N; i++)
    buffer[i] = points[i];
  merge_sort(buffer + 1, points + 1, N - 1);
  cout << points[0].id << ' ' << points[N / 2].id << endl;

  return 0;
}
