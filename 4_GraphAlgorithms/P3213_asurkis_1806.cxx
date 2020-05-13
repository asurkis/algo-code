#include <cstdint>
#include <iostream>
#include <unordered_map>
#include <unordered_set>
#include <vector>

using namespace std;

struct Node {
  int64_t number;
  int64_t came_from;
  int64_t min_time;
  int64_t display_as;
};

int64_t n;
int64_t transmission_time[10];
int64_t first, last;
unordered_map<int64_t, Node> nodes;
unordered_set<int64_t> queue;

void check_edge(const Node &current_node, int64_t other_number,
                int prefix_len) {
  if (other_number == current_node.number)
    return;
  if (!nodes.count(other_number))
    return;
  Node &other_node = nodes[other_number];
  int64_t time = current_node.min_time + transmission_time[9 - prefix_len];
  if (time < other_node.min_time) {
    other_node.min_time = time;
    other_node.came_from = current_node.number;
    if (!queue.count(other_number))
      queue.insert(other_number);
  }
}

int main() {
  cin >> n;
  for (int64_t i = 0; i < 10; ++i)
    cin >> transmission_time[i];

  nodes.reserve(n);
  for (int64_t i = 0; i < n; ++i) {
    Node node;
    cin >> node.number;
    node.min_time = INT64_MAX;
    node.came_from = -1;
    node.display_as = i + 1;
    if (i == 0) {
      first = node.number;
      node.min_time = 0;
    }
    if (i + 1 == n)
      last = node.number;
    nodes[node.number] = node;
  }

  queue.insert(first);
  while (!queue.empty()) {
    auto min_iter = begin(queue);
    // for (auto iter = begin(queue); iter != end(queue); ++iter)
    //   if (nodes[*iter].min_time < nodes[*min_iter].min_time)
    //     min_iter = iter;

    int64_t current_number = *min_iter;
    Node current_node = nodes[current_number];
    queue.erase(min_iter);

    for (int64_t i = 0, di = 1; i < 10; ++i, di *= 10) {
      for (int64_t j = 0; j < 10; ++j) {
        int64_t other_number =
            current_number + (j - current_number / di % 10) * di;
        check_edge(current_node, other_number, i);
      }

      for (int64_t j = 0, dj = 1; j < i; ++j, dj *= 10) {
        int64_t other_number =
            current_number +
            (current_number / dj % 10 - current_number / di % 10) * di +
            (current_number / di % 10 - current_number / dj % 10) * dj;
        check_edge(current_node, other_number, i);
      }
    }
  }

  vector<Node> path;
  path.push_back(nodes[last]);
  while (path[path.size() - 1].came_from != -1)
    path.push_back(nodes[path[path.size() - 1].came_from]);

  if (path.size() > 1) {
    cout << path[0].min_time << endl;
    cout << path.size() << endl;
    while (!path.empty()) {
      cout << path[path.size() - 1].display_as << ' ';
      path.pop_back();
    }
    cout << endl;
  } else {
    cout << -1 << endl;
  }

  return 0;
}
