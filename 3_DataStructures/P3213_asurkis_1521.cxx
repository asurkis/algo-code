#include <iostream>

using namespace std;

int N, K, Q;
int bintree[0x40000];

void trigger_update(int from) {
  if (!from)
    return;
  auto up = (from - 1) / 2;
  bintree[up] = bintree[2 * up + 1] + bintree[2 * up + 2];
  trigger_update(up);
}

int pos_index(int pos) {
  int index = 0;
  int current_pos = 0;
  while (index + 1 < Q) {
    int left = 2 * index + 1;
    if (current_pos + bintree[left] <= pos) {
      current_pos += bintree[left];
      index = left + 1;
    } else {
      index = left;
    }
  }
  return index;
}

int main() {
  cin >> N >> K;
  Q = 1;
  while (Q < N)
    Q *= 2;

  for (int i = 0; i < Q; ++i) {
    bintree[i + Q - 1] = i < N ? 1 : 0;
    trigger_update(i + Q - 1);
  }

  int pos = 0;
  while (bintree[0]) {
    pos = (pos + K - 1) % bintree[0];
    int index = pos_index(pos);
    cout << index + 2 - Q << ' ';
    --bintree[index];
    trigger_update(index);
  }

  return 0;
}
