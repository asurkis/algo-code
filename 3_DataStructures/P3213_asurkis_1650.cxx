#include <cstdint>
#include <iostream>
#include <map>
#include <memory>
#include <string>
#include <unordered_map>
#include <vector>

using namespace std;

struct City {
  uint64_t wealth;
  uint64_t days_max;
  int heap_pos;

  City() : wealth(0), days_max(0), heap_pos(0) {}
};

struct Billionaire {
  uint64_t wealth;
  shared_ptr<City> location;

  Billionaire() : wealth(0), location(nullptr) {}
};

map<string, shared_ptr<City>> cities;
vector<shared_ptr<City>> heap;
unordered_map<string, Billionaire> billionaires;

bool comparator_for_heap(const shared_ptr<City> &a, const shared_ptr<City> &b) {
  return a->wealth > b->wealth;
}

shared_ptr<City> persist_city(const string &key) {
  if (!cities.count(key)) {
    auto new_city = make_shared<City>();
    new_city->heap_pos = cities.size();

    cities[key] = new_city;
    heap.push_back(new_city);
  }
  return cities[key];
}

void sift_down(int pos) {
  while (true) {
    int candidate = pos;
    for (int alt = 2 * pos + 1; alt <= 2 * pos + 2; ++alt)
      if (alt < heap.size() && heap[candidate]->wealth < heap[alt]->wealth)
        candidate = alt;
    if (pos == candidate)
      break;
    swap(heap[candidate], heap[pos]);
    heap[pos]->heap_pos = pos;
    heap[candidate]->heap_pos = candidate;
    pos = candidate;
  }
}

void sift_up(int pos) {
  while (pos > 0) {
    int alt = (pos - 1) / 2;
    if (heap[alt]->wealth < heap[pos]->wealth) {
      swap(heap[alt], heap[pos]);
      heap[pos]->heap_pos = pos;
      heap[alt]->heap_pos = alt;
      pos = alt;
    } else {
      break;
    }
  }
}

void increment_days_max(uint64_t amount) {
  bool valid = !cities.empty();
  for (int i = 1; i <= 2; ++i)
    valid &= cities.size() <= i || heap[i]->wealth < heap[0]->wealth;
  if (valid)
    heap[0]->days_max += amount;
}

int main() {
  int n;
  cin >> n;
  for (int i = 0; i < n; ++i) {
    string billionaire_name, city_name;
    Billionaire new_billionaire;
    cin >> billionaire_name >> city_name >> new_billionaire.wealth;
    auto city = persist_city(city_name);
    new_billionaire.location = city;
    city->wealth += new_billionaire.wealth;
    billionaires[billionaire_name] = move(new_billionaire);
  }

  for (int i = cities.size() / 2; ~i; --i)
    sift_down(i);

  int m, k;
  cin >> m >> k;
  uint64_t prev_day = 0;
  for (int i = 0; i < k; ++i) {
    uint64_t day;
    string billionaire_name, next_city_name;
    cin >> day >> billionaire_name >> next_city_name;
    increment_days_max(day - prev_day);
    prev_day = day;
    auto &billionaire = billionaires[billionaire_name];
    auto prev_city = billionaire.location;
    auto next_city = persist_city(next_city_name);
    billionaire.location = next_city;
    prev_city->wealth -= billionaire.wealth;
    sift_down(prev_city->heap_pos);
    next_city->wealth += billionaire.wealth;
    sift_up(next_city->heap_pos);
  }
  increment_days_max(m - prev_day);

  for (auto iter = begin(cities); iter != end(cities); ++iter)
    if (iter->second->days_max)
      cout << iter->first << ' ' << iter->second->days_max << endl;
  return 0;
}
