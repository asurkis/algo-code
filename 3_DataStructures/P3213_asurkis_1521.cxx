#include <iostream>
#include <vector>

using namespace std;

int main() {
  int N, K;
  cin >> N >> K;
  vector<size_t> order;
  for (size_t i = 0; i < N; ++i)
    order.push_back(i + 1);

  size_t pos = 0;
  for (size_t i = 0; i < N; ++i) {
    pos = (pos + K - 1) % order.size();
    // cout << order[pos] << ' ';
    order.erase(begin(order) + pos);
  }
  return 0;
}
