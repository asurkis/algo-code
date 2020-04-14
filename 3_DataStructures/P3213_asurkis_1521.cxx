#include <iostream>
#include <vector>

using namespace std;

size_t N, K, Nup;
size_t bintree[0x40000];

void trigger_update(size_t from) {
  if (!from)
    return;
  size_t up = (from - 1) / 2;
  bintree[up] = bintree[2 * up + 1] + bintree[2 * up + 2];
  trigger_update(up);
}

size_t pos_index(size_t pos) {
  size_t index = 0;
  size_t current_pos = 0;
  while (index + 1 < Nup) {
    size_t left = 2 * index + 1;
    if (current_pos + bintree[left] <= pos) {
      current_pos += bintree[left];
      index = left + 1;
    } else {
      index = left;
    }
  }
  return index + 1 - Nup;
}

int main() {
  cin >> N >> K;
  Nup = N;
  while (Nup & (Nup - 1))
    Nup &= (Nup - 1);
  if (N != Nup)
    Nup *= 2;

  for (size_t i = 0; i < Nup; ++i) {
    bintree[i + Nup - 1] = i < N ? 1 : 0;
    trigger_update(i + Nup - 1);
  }

  size_t pos = 0;
  while (bintree[0]) {
    pos = (pos + K - 1) % bintree[0];
    size_t index = pos_index(pos);
    cout << index + 1 << ' ';
    --bintree[index + Nup - 1];
    trigger_update(index + Nup - 1);
  }

  return 0;
}
