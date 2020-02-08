#include <iostream>

using namespace std;

int main() {
  int N;
  cin >> N;

  int global_max = 0;
  int current = 0;

  for (int i = 0; i < N; i++) {
    int p;
    cin >> p;

    current += p;
    if (current < 0)
      current = 0;
    if (current > global_max)
      global_max = current;
  }
  if (current > global_max)
    global_max = current;

  cout << global_max << endl;
  return 0;
}
