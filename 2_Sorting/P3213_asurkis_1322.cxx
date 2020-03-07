#include <iostream>

using namespace std;

char chr[] = "ABCDEFGHIJKLMNOPQRSTUVWXYZ_abcdefghijklmnopqrstuvwxyz";
int ord[256];

struct Char {
  int pos;
  char val;
};

char last_col[100001];
Char chars[100000];

bool operator<(const Char &a, const Char &b) {
  if (ord[a.val] == ord[b.val])
    return a.pos < b.pos;
  return ord[a.val] < ord[b.val];
}

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

int main() {
  for (int i = 0; i < 256; ++i)
    ord[i] = -1;
  for (int i = 0; chr[i] != '\0'; ++i)
    ord[chr[i]] = i;

  int K;
  cin >> K >> last_col;

  int n = 0;
  while (last_col[n] != '\0') {
    chars[n].pos = n;
    chars[n].val = last_col[n];
    ++n;
  }

  if (!n)
    return 0;

  quick_sort(chars, chars + n);

  --K;
  for (int i = 0; i < n; ++i)
    cout << last_col[K = chars[K].pos];
  cout << endl;

  return 0;
}
