#include <iostream>
#include <utility>

using namespace std;

pair<int, int> find_angle(int coord, int size) {
  pair<int, int> result;
  int high = coord >> size;
  int high_and_1 = high & 1;
  int high_or_1 = high | 1;
  int high_increased = high_or_1 << size;
  result.first = high_increased - (high_and_1 ^ 1);
  result.second = high_increased - high_and_1;
  return result;
}

int field[512][512];
int shift = 0;

void fill(int x, int y, int size) {
  if (size < 0) {
    field[x][y] = shift;
    return;
  }

  pair<int, int> angle_x = find_angle(x, size);
  pair<int, int> angle_y = find_angle(y, size);

  fill(x, y, size - 1);
  fill(angle_x.first, angle_y.second, size - 1);
  fill(angle_x.second, angle_y.second, size - 1);
  fill(angle_x.second, angle_y.first, size - 1);

  shift++;
  field[angle_x.second][angle_y.first] = shift;
  field[angle_x.second][angle_y.second] = shift;
  field[angle_x.first][angle_y.second] = shift;
}

int main() {
  int n, x, y;
  cin >> n >> x >> y;

  fill(x - 1, y - 1, n - 1);

  for (int i = 0; i < (1 << n); i++) {
    for (int j = 0; j < (1 << n); j++) {
      cout << field[i][j] << ' ';
    }
    cout << endl;
  }
  return 0;
}
