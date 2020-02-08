#include <algorithm>
#include <iostream>

using namespace std;

int n;
int w[20];
int pw1 = 0;
int pw2 = 0;

int recursion(int from = 0) {
  if (from == n) {
    return abs(pw1 - pw2);
  }

  pw1 += w[from];
  int r1 = recursion(from + 1);
  pw1 -= w[from];
  pw2 += w[from];
  int r2 = recursion(from + 1);
  pw2 -= w[from];

  return min(r1, r2);
}

int main() {
  cin >> n;
  for (int i = 0; i < n; i++)
    cin >> w[i];
  cout << recursion() << endl;
  return 0;
}