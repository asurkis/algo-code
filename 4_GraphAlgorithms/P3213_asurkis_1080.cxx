#include <cstdint>
#include <iostream>
#include <vector>

using namespace std;

uint8_t const ALLOWED_RED = 1;
uint8_t const ALLOWED_BLUE = 2;
uint8_t const ALLOWED_ANY = ALLOWED_RED | ALLOWED_BLUE;
uint8_t const VISITED = 4;

vector<uint8_t> nodes;
vector<bool> connectivity;

bool collapse(size_t pos) {
  auto &n = nodes[pos];
  if (!(n & ALLOWED_ANY))
    return false;
  if (n & VISITED)
    return true;
  auto a = n;
  n |= VISITED;
  if (!a)
    return false;
  for (size_t i = 0; i < nodes.size(); ++i) {
    if (!connectivity[pos * nodes.size() + i])
      continue;
    nodes[i] &= ~a;
    if (!collapse(i))
      return false;
  }
  return true;
}

int main() {
  size_t N;
  cin >> N;

  for (size_t i = 0; i < N; ++i)
    nodes.push_back(ALLOWED_ANY);
  for (size_t i = 0; i < N * N; ++i)
    connectivity.push_back(false);

  for (size_t i = 0; i < N; ++i) {
    for (;;) {
      size_t j;
      cin >> j;
      if (!j--)
        break;
      connectivity[i * N + j] = true;
      connectivity[j * N + i] = true;
    }
  }

  for (size_t i = 0; i < N; ++i) {
    if (nodes[i] == ALLOWED_ANY) {
      nodes[i] = ALLOWED_RED;
      if (!collapse(i)) {
        cout << "-1" << endl;
        return 0;
      }
    }
  }

  for (size_t i = 0; i < N; ++i)
    cout << ((nodes[i] & ALLOWED_RED) ? '0' : '1');
  cout << endl;

  return 0;
}
