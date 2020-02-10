#include <algorithm>
#include <iostream>
#include <limits>
#include <string>
#include <utility>
#include <vector>

using namespace std;

struct SignType {
  int id;
  int count;
};

bool operator<(const SignType &a, const SignType &b) {
  return a.count < b.count;
}

int main() {
  int k;
  cin >> k;
  vector<SignType> signs(k);
  for (int i = 0; i < k; i++) {
    signs[i].id = i + 1;
    cin >> signs[i].count;
  }

  sort(signs.begin(), signs.end());

  while (!signs.empty()) {
    int count = signs[signs.size() - 1].count;
    for (size_t i = signs.size() - 1;
         i < signs.size() && signs[i].count == count; i--) {
      cout << signs[i].id << ' ';
      signs[i].count--;
      if (signs[i].count == 0) {
        signs.erase(signs.begin() + i);
      }
    }
  }
  cout << endl;

  return 0;
}