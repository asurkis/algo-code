#include <iostream>
#include <vector>

using namespace std;

struct Edge {
  double rate, com;
  size_t other;
};

struct Node {
  vector<Edge> edges;
  double maxval;
};

int main() {
  size_t N, M, S;
  double V;
  cin >> N >> M >> S >> V;
  --S;

  vector<Node> nodes(N);

  for (size_t i = 0; i < M; ++i) {
    size_t a, b;
    double rab, cab, rba, cba;
    cin >> a >> b >> rab >> cab >> rba >> cba;
    --a, --b;
    Edge e;

    e.other = b;
    e.rate = rab;
    e.com = cab;
    nodes[a].edges.push_back(e);

    e.other = a;
    e.rate = rba;
    e.com = cba;
    nodes[b].edges.push_back(e);
  }

  vector<size_t> queue;
  nodes[S].maxval = V;
  queue.push_back(S);

  for (size_t pos = 0; pos < queue.size(); ++pos) {
    size_t n = queue[pos];
    for (auto iter = begin(nodes[n].edges); iter != end(nodes[n].edges);
         ++iter) {
      double curval = (nodes[n].maxval - iter->com) * iter->rate;
      if (curval > nodes[iter->other].maxval) {
        if (iter->other == S) {
          cout << "YES" << endl;
          return 0;
        }
        nodes[iter->other].maxval = curval;
        queue.push_back(iter->other);
      }
    }
  }

  cout << "NO" << endl;
  return 0;
}
