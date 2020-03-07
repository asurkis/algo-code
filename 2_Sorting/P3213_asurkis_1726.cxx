#include <iostream>

using namespace std;

typedef long long Long;

Long n;
Long x[100000];
Long y[100000];
Long buf[100000];

void merge_sort(Long *src, Long *dst, Long size) {
  if (size < 2)
    return;
  Long m = size / 2;
  merge_sort(dst, src, m);
  merge_sort(dst + m, src + m, size - m);

  for (Long i = 0; i + i < size - m; i++)
    swap(src[m + i], src[size - i - 1]);

  Long l = 0;
  Long r = size - 1;
  for (Long i = 0; i < size; i++)
    dst[i] = src[src[r] < src[l] ? r-- : l++];
}

int main() {
  cin >> n;
  for (Long i = 0; i < n; i++)
    cin >> x[i] >> y[i];
  for (Long i = 0; i < n; i++)
    buf[i] = x[i];
  merge_sort(buf, x, n);
  for (Long i = 0; i < n; i++)
    buf[i] = y[i];
  merge_sort(buf, y, n);

  Long sum = 0;
  for (Long i = 1; i < n; i++)
    sum += i * (n - i) * (x[i] - x[i - 1] + y[i] - y[i - 1]);
  cout << 2 * sum / n / (n - 1) << endl;
  return 0;
}
