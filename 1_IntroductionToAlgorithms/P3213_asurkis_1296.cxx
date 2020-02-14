#include <iostream>

using namespace std;

struct Slice {
  int start;
  int end;
  int sum;
};

struct RecursionResult {
  Slice all;
  Slice max;
  Slice left;
  Slice right;
};

int elements[60000];

RecursionResult recursion(int start, int size) {
  RecursionResult result;

  if (size < 2) {
    result.all.start = start;
    result.all.end = start + size;
    result.all.sum = size == 1 ? elements[start] : 0;
    if (result.all.sum > 0) {
      result.max = result.all;
      result.left = result.all;
      result.right = result.all;
    } else {
      result.left.start = start;
      result.left.end = start;
      result.left.sum = 0;

      result.max = result.left;

      result.right.start = start + size;
      result.right.end = start + size;
      result.right.sum = 0;
    }
    return result;
  }

  RecursionResult left = recursion(start, size / 2);
  RecursionResult right = recursion(start + size / 2, (size + 1) / 2);

  result.all.start = left.left.start;
  result.all.end = right.right.end;
  result.all.sum = left.all.sum + right.all.sum;

  result.max = left.max;
  if (right.max.sum > result.max.sum)
    result.max = right.max;
  if (left.right.sum + right.left.sum > result.max.sum) {
    result.max.start = left.right.start;
    result.max.end = right.left.end;
    result.max.sum = left.right.sum + right.left.sum;
  }

  result.left = left.left;
  if (left.all.sum + right.left.sum > result.left.sum) {
    result.left.start = left.all.start;
    result.left.end = right.left.end;
    result.left.sum = left.all.sum + right.left.sum;
  }

  result.right = right.right;
  if (left.right.sum + right.all.sum > result.right.sum) {
    result.right.start = left.right.start;
    result.right.end = right.all.end;
    result.right.sum = left.right.sum + right.all.sum;
  }

  return result;
}

int main() {
  int N;
  cin >> N;

  for (int i = 0; i < N; i++)
    cin >> elements[i];

  RecursionResult r = recursion(0, N);
  cout << (r.max.sum > 0 ? r.max.sum : 0) << endl;

  return 0;
}
