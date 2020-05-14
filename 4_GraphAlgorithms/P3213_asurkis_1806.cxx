#include <algorithm>
#include <cstdint>
#include <iostream>
#include <unordered_map>
#include <vector>

using namespace std;

struct Edge {
  size_t o;
  int64_t w;
};

struct Node {
  vector<Edge> edges;
  size_t came_from;
  int64_t min_time;
};

int64_t const INFINITY = 0x7FFFFFFF;
int64_t transmission_time[10];
vector<Node> nodes;
vector<size_t> heap;
vector<size_t> path;
unordered_map<int64_t, size_t> node_by_number;

void sift_up(size_t pos) {
  while (pos != 0) {
    size_t alt = (pos - 1) / 2;
    if (heap[pos] < heap[alt]) {
      swap(heap[pos], heap[alt]);
      pos = alt;
    } else {
      break;
    }
  }
}

void sift_down(size_t pos) {
  for (;;) {
    size_t alt = pos;
    if (2 * pos + 1 < heap.size() && heap[2 * pos + 1] < heap[alt])
      alt = 2 * pos + 1;
    if (2 * pos + 2 < heap.size() && heap[2 * pos + 2] < heap[alt])
      alt = 2 * pos + 2;
    if (alt == pos)
      break;
    swap(heap[pos], heap[alt]);
    pos = alt;
  }
}

void check_edge(const pair<int64_t, size_t> &current, int64_t other_number,
                int prefix_len) {
  if (current.first == other_number)
    return;
  if (!node_by_number.count(other_number))
    return;
  nodes[current.second].edges.push_back(
      {node_by_number[other_number], transmission_time[prefix_len]});
}

bool edge_comparator(const Edge &a, const Edge &b) {
  if (a.o < b.o)
    return true;
  if (a.o > b.o)
    return false;
  if (a.w < b.w)
    return true;
  return false;
}

int main() {
  size_t n;
  cin >> n;
  nodes.resize(n);
  for (size_t i = 0; i < 10; ++i)
    cin >> transmission_time[i];
  for (size_t i = 0; i < n; ++i) {
    int64_t number;
    cin >> number;
    node_by_number[number] = i;
    nodes[i].min_time = INFINITY;
    nodes[i].came_from = ~0;
  }

  for (auto iter = begin(node_by_number); iter != end(node_by_number); ++iter) {
    int64_t current_number = iter->first;
    for (int64_t i = 0, mi = 1; i < 10; ++i, mi *= 10) {
      for (int64_t j = 0; j < 10; ++j) {
        int64_t other_number =
            current_number + (j - current_number / mi % 10) * mi;
        check_edge(*iter, other_number, 9 - i);
      }
      for (int64_t j = 0, mj = 1; j < i; ++j, mj *= 10) {
        int64_t other_number =
            current_number +
            (current_number / mj % 10 - current_number / mi % 10) * mi +
            (current_number / mi % 10 - current_number / mj % 10) * mj;
        check_edge(*iter, other_number, 9 - i);
      }
    }
  }

  for (auto iter = begin(nodes); iter != end(nodes); ++iter) {
    auto &edges = iter->edges;
    sort(begin(edges), end(edges), edge_comparator);
    for (size_t i = 0; i + 1 < edges.size();) {
      if (edges[i].o == edges[i + 1].o) {
        edges.erase(begin(edges) + (i + 1));
      } else {
        ++i;
      }
    }
  }

  nodes[0].min_time = 0;
  heap.push_back(0);
  while (!heap.empty()) {
    size_t current = heap[0];
    heap[0] = heap[heap.size() - 1];
    heap.pop_back();
    sift_down(0);

    auto &current_node = nodes[current];
    auto &edges = current_node.edges;
    for (auto iter = begin(edges); iter != end(edges); ++iter) {
      auto &other = nodes[iter->o];
      int64_t time = current_node.min_time + iter->w;
      if (time < other.min_time) {
        other.min_time = time;
        other.came_from = current;
        heap.push_back(iter->o);
        sift_up(heap.size() - 1);
      }
    }
  }

  path.push_back(nodes.size() - 1);
  while (nodes[path[path.size() - 1]].came_from != ~0)
    path.push_back(nodes[path[path.size() - 1]].came_from);

  if (path.size() > 1) {
    cout << nodes[nodes.size() - 1].min_time << endl;
    cout << path.size() << endl;
    for (size_t i = path.size(); i != 0; --i)
      cout << path[i - 1] + 1 << ' ';
    cout << endl;
  } else {
    cout << -1 << endl;
  }
  return 0;
}
