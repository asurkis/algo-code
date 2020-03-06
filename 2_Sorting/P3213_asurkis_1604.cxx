#include <iostream>

using namespace std;

struct Sign {
  int id;
  int count;
};

bool operator<(const Sign &a, const Sign &b) { return a.count < b.count; }

void merge_sort(Sign *src, Sign *dst, int size) {
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
    dst[i] = src[src[l] < src[r] ? r-- : l++];
}

int k;
Sign n[10000];
Sign buf[10000];

int main() {
  cin >> k;
  int total = 0;
  for (int i = 0; i < k; i++) {
    n[i].id = i + 1;
    cin >> n[i].count;
    total += n[i].count;
    buf[i] = n[i];
  }

  merge_sort(buf, n, k);

  int current = 0;
  while (current < total) {
    cout << n[0].id << ' ';
    n[0].count--;
    current++;
    if (k == 1)
      continue;

    if (n[0].count + 1 == n[1].count) {
      for (int i = 1; i < k; i++) {
        if (n[0].count + 1 == n[i].count) {
          cout << n[i].id << ' ';
          n[i].count--;
          current++;
        }
      }
    } else if (n[1].count) {
      cout << n[1].id << ' ';
      n[1].count--;
      current++;

      int i = 1;
      while (i + 1 < k && n[i].count < n[i + 1].count) {
        swap(n[i], n[i + 1]);
        i++;
      }
    }
  }
  return 0;
}
