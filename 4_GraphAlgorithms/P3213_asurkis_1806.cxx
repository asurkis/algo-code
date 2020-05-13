#include <cstdint>
#include <iostream>
#include <unordered_map>
#include <unordered_set>

using namespace std;

struct Node {
  int64_t number;
  int64_t min_time;
  size_t display_as;
};

int main() {
  size_t n;
  int64_t transmission_time[10];
  cin >> n;
  for (size_t i = 0; i < 10; ++i)
    cin >> transmission_time[i];

  unordered_map<int64_t, Node> nodes;
  nodes.reserve(n);

  for (size_t i = 0; i < n; ++i) {
    Node n;
    cin >> n.number;
    n.min_time = INT64_MAX;
    n.display_as = i + 1;
  }


  return 0;
}
