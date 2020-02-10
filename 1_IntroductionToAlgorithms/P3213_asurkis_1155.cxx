#include <iostream>

using namespace std;

struct Edge {
  int v1, v2;
};

enum { A = 0, B, C, D, E, F, G, H };
char const names[] = "ABCDEFGH";
Edge edges[] = {
    {A, B}, {C, D}, {E, F}, {G, H}, {A, D}, {B, C},
    {E, H}, {F, G}, {A, E}, {B, F}, {C, G}, {D, H},
};

int main() {
  int count[8];
  for (int i = 0; i < 8; i++)
    cin >> count[i];

  int n1 = count[A] + count[C] + count[F] + count[H];
  int n2 = count[B] + count[D] + count[E] + count[G];

  if (n1 != n2) {
    cout << "IMPOSSIBLE" << endl;
    return 0;
  }

  while (n1 != 0) {
    for (int i = 0; i < 12; i++) {
      Edge &e = edges[i];
      while (count[e.v1] > 0 && count[e.v2] > 0) {
        cout << names[e.v1] << names[e.v2] << '-' << endl;
        count[e.v1]--;
        count[e.v2]--;
        n1--;
        n2--;
      }
    }

    while (count[C] > 0) {
      cout << "AB+" << endl << "BC-" << endl;
      count[C]--;
      count[A]++;
    }

    while (count[F] > 0) {
      cout << "AB+" << endl << "BF-" << endl;
      count[F]--;
      count[A]++;
    }

    while (count[H] > 0) {
      cout << "AD+" << endl << "DH-" << endl;
      count[H]--;
      count[A]++;
    }

    while (count[G] > 0) {
      cout << "BC+" << endl << "CG-" << endl;
      count[G]--;
      count[B]++;
    }

    for (int i = 0; i < 12; i++) {
      Edge &e = edges[i];
      while (count[e.v1] > 0 && count[e.v2] > 0) {
        cout << names[e.v1] << names[e.v2] << '-' << endl;
        count[e.v1]--;
        count[e.v2]--;
        n1--;
        n2--;
      }
    }
  }

  return 0;
}