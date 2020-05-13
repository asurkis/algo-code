#include <algorithm>
#include <iostream>
#include <vector>

using namespace std;

struct Edge {
  size_t a, b;
  int weight;
  bool used;
};

bool comparator(const Edge &a, const Edge &b) { return a.weight < b.weight; }

int main() {
  size_t N, M;
  cin >> N >> M;
  vector<size_t> nodes(N);
  for (size_t i = 0; i < N; ++i)
    nodes[i] = i;
  vector<Edge> edges(M);
  for (size_t i = 0; i < M; ++i) {
    Edge &e = edges[i];
    cin >> e.a >> e.b >> e.weight;
    --e.a, --e.b;
    e.used = false;
  }
  sort(begin(edges), end(edges), comparator);

  int maxweight = 0;
  size_t used_number = 0;
  for (auto e = begin(edges); e != end(edges); ++e) {
    if (nodes[e->a] != nodes[e->b]) {
      maxweight = e->weight;
      e->used = true;
      ++used_number;
      auto mn = nodes[e->a], mx = nodes[e->b];
      if (mn > mx)
        swap(mn, mx);
      for (auto n = begin(nodes); n != end(nodes); ++n) {
        if (*n == mx)
          *n = mn;
      }
    }
  }

  cout << maxweight << endl << used_number << endl;
  for (auto e = begin(edges); e != end(edges); ++e) {
    if (e->used)
      cout << e->a + 1 << ' ' << e->b + 1 << endl;
  }
  return 0;
}
