#include <iostream>

using namespace std;

struct Sign {
  int id;
  int count;
};

bool operator<(const Sign &a, const Sign &b) { return a.count < b.count; }

int sift_down(Sign *arr, int size, int pos) {
  while (true) {
    int candidate = pos;
    for (int i = 2 * pos + 1; i <= 2 * pos + 2; ++i)
      if (i < size && arr[candidate] < arr[i])
        candidate = i;
    if (candidate == pos)
      break;
    swap(arr[pos], arr[candidate]);
    pos = candidate;
  }
  return pos;
}

int k;
Sign n[10000];

int main() {
  cin >> k;
  for (int i = 0; i < k; ++i) {
    n[i].id = i + 1;
    cin >> n[i].count;
  }

  for (int i = k / 2 - 1; i >= 0; --i)
    sift_down(n, k, i);

  while (n[0].count > 0) {
    cout << n[0].id << ' ';
    --n[0].count;
    if (k <= 1)
      continue;

    int next_to_remove = n[1] < n[2] ? 2 : 1;
    if (n[next_to_remove].count <= 0)
      continue;
    cout << n[next_to_remove].id << ' ';
    --n[next_to_remove].count;
    sift_down(n, k, next_to_remove);
    sift_down(n, k, 0);
  }
  return 0;
}
