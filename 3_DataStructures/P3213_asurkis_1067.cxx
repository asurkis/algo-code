#include <iostream>
#include <map>
#include <memory>
#include <string>

using namespace std;

struct Node {
  map<string, shared_ptr<Node>> children;

  shared_ptr<Node> persist(const string &key) {
    if (!children.count(key))
      children[key] = make_shared<Node>();
    return children[key];
  }
};

void print(const shared_ptr<Node> &n, int shift = 0) {
  for (auto iter = begin(n->children); iter != end(n->children); ++iter) {
    for (int i = 0; i < shift; ++i)
      cout << ' ';
    cout << iter->first << '\n';
    print(iter->second, shift + 1);
  }
}

int main() {
  int N;
  cin >> N;
  string path;
  getline(cin, path);
  auto root = make_shared<Node>();
  for (int i = 0; i < N; ++i) {
    getline(cin, path);
    auto ptr = root;
    while (true) {
      auto pos = path.find('\\');
      auto dirname = path.substr(0, pos);
      ptr = ptr->persist(dirname);
      if (!~pos)
        break;
      path = path.substr(pos + 1);
    }
  }
  print(root);
  return 0;
}
