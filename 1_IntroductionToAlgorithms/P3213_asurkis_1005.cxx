#include <algorithm>
#include <iostream>

using namespace std;

int stone_count;
int stone_weights[20];
int pile_weight_1 = 0;
int pile_weight_2 = 0;

int recursion(int from = 0) {
  if (from == stone_count) {
    return abs(pile_weight_1 - pile_weight_2);
  }

  pile_weight_1 += stone_weights[from];
  int result_1 = recursion(from + 1);
  pile_weight_1 -= stone_weights[from];
  pile_weight_2 += stone_weights[from];
  int result_2 = recursion(from + 1);
  pile_weight_2 -= stone_weights[from];

  return min(result_1, result_2);
}

int main() {
  cin >> stone_count;
  for (int i = 0; i < stone_count; i++)
    cin >> stone_weights[i];
  cout << recursion() << endl;
  return 0;
}
