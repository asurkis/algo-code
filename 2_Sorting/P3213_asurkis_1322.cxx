#include <algorithm>
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

int main() {
  for (int i = 0; i < 256; i++)
    ord[i] = -1;
  for (int i = 0; chr[i] != '\0'; i++)
    ord[chr[i]] = i;

  int K;
  cin >> K >> last_col;

  int n = 0;
  while (last_col[n] != '\0') {
    chars[n].pos = n;
    chars[n].val = last_col[n];
    n++;
  }

  if (n == 0)
    return 0;

  sort(chars, chars + n);

  K--;
  for (int i = 0; i < n; i++)
    cout << last_col[K = chars[K].pos];
  cout << endl;

  return 0;
}
