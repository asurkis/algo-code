#include <iostream>
#include <vector>

using namespace std;

int main() {
  int N;
  cin >> N;

  vector<int> stack;
  int ball = 1;
  for (int i = 0; i < N; ++i) {
    int top;
    cin >> top;
    if (empty(stack))
      stack.push_back(ball++);
    if (stack.back() > top) {
      cout << "Cheater" << endl;
      return 0;
    }
    while (stack.back() < top)
      stack.push_back(ball++);
    stack.pop_back();
  }
  cout << "Not a proof" << endl;
  return 0;
}
