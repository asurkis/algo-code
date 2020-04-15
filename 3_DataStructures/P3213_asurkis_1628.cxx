#include <algorithm>
#include <iostream>
#include <vector>

using namespace std;

struct Point {
  int x;
  int y;
};

bool operator==(const Point &a, const Point &b) {
  return a.x == b.x && a.y == b.y;
}

bool first_comparator(const Point &a, const Point &b) {
  if (a.x != b.x)
    return a.x < b.x;
  return a.y < b.y;
}

bool second_comparator(const Point &a, const Point &b) {
  if (a.y != b.y)
    return a.y < b.y;
  return a.x < b.x;
}

int main() {
  int m, n, k;
  cin >> m >> n >> k;
  vector<Point> blacks(k + 1);
  for (int i = 0; i < k; ++i)
    cin >> blacks[i].x >> blacks[i].y;
  blacks[k].x = m + 1;
  blacks[k].y = n + 1;

  int result = 0;
  vector<Point> excluded(1);
  excluded[0].x = m + 1;
  excluded[0].y = n + 1;

  sort(begin(blacks), end(blacks), first_comparator);
  vector<Point>::iterator iter_blacks, iter_excluded;
  Point position;

  iter_blacks = begin(blacks);
  for (position.x = 1; position.x <= m; ++position.x) {
    position.y = 1;
    while (iter_blacks->x == position.x) {
      if (iter_blacks->y == position.y + 1) {
        excluded.push_back(position);
      } else if (iter_blacks->y > position.y + 1) {
        ++result;
      }
      position.y = iter_blacks->y + 1;
      ++iter_blacks;
    }
    if (n == position.y) {
      excluded.push_back(position);
    } else if (n > position.y) {
      ++result;
    }
  }

  sort(begin(blacks), end(blacks), second_comparator);
  sort(begin(excluded), end(excluded), second_comparator);

  iter_blacks = begin(blacks);
  iter_excluded = begin(excluded);
  for (position.y = 1; position.y <= n; ++position.y) {
    position.x = 1;
    while (iter_blacks->y == position.y) {
      if (iter_blacks->x == position.x + 1) {
        while (second_comparator(*iter_excluded, position))
          ++iter_excluded;
        if (*iter_excluded == position)
          ++result;
      } else if (iter_blacks->x > position.x + 1) {
        ++result;
      }
      position.x = iter_blacks->x + 1;
      ++iter_blacks;
    }
    if (m == position.x) {
      while (second_comparator(*iter_excluded, position))
        ++iter_excluded;
      if (*iter_excluded == position)
        ++result;
    } else if (m > position.x) {
      ++result;
    }
  }

  cout << result << endl;
  return 0;
}
