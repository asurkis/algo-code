#include <algorithm>
#include <cstdint>
#include <cstdio>
#include <vector>

using namespace std;

struct Edge {
  size_t a, b;
  int64_t price;
};

int main() {
  size_t N, M;
  scanf("%d%d", &N, &M);
  vector<int64_t> nodes(N, -1);
  vector<Edge> edges(M);
  for (size_t i = 0; i < M; ++i) {
    scanf("%d%d%d", &edges[i].a, &edges[i].b, &edges[i].price);
    --edges[i].a, --edges[i].b;
  }
  size_t S, F;
  scanf("%d%d", &S, &F);
  --S, --F;

  nodes[S] = 0;
  for (;;) {
    bool changed = false;
    for (auto iter = begin(edges); iter != end(edges); ++iter) {
      int64_t pa = nodes[iter->a];
      int64_t &pb = nodes[iter->b];
      int64_t pn = pa + iter->price;
      if (pa >= 0 && pn > pb) {
        pb = pn;
        changed = true;
      }
    }
    if (!changed)
      break;
  }

  if (nodes[F] >= 0) {
    printf("%d\n", nodes[F]);
  } else {
    puts("No solution\n");
  }

  return 0;
}
