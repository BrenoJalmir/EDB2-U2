#include <iostream>
#include <vector>
#include <cmath>

struct node {
  int key;
  // int priority;
  struct node *left;
  struct node *right;
  typedef struct node knot;
};

void printVector(std::vector<int> v) {
  for (int i = 0; i < v.size(); i++) {
    std::cout << v[i] << " ";
  }
  std::cout << std::endl;
}

void switchPos(std::vector<int>& v, int index1, int index2) {
  int temp = v[index1];
  v[index1] = v[index2];
  v[index2] = temp;
}

void descend(std::vector<int>& v, int index) {
  int biggerPriorityIndex = index;
  int vSize = v.size();
  if (index * 2 + 1 < vSize && v[2*index + 1] > v[biggerPriorityIndex]) biggerPriorityIndex = 2 * index + 1;
  if (index * 2 + 2 < vSize && v[2*index + 2] > v[biggerPriorityIndex]) biggerPriorityIndex = 2 * index + 2;
  if (biggerPriorityIndex != index) {
    switchPos(v, index, biggerPriorityIndex);
    descend(v, biggerPriorityIndex);
  }
}

void ascend(std::vector<int>& v, int index) {
  int father = floor((index - 1)/2);
  if (v[index] > v[father]) {
    switchPos(v, index, father);
    ascend(v, father);
  }
}

void alterPriority(std::vector<int>& v, int index, int newPriority) {
  void (*action)(std::vector<int>&, int);
  if (v[index] >= newPriority) action = descend;
  else action = ascend;
  v[index] = newPriority;
  action(v, index);
}

void insertOnHeap(std::vector<int>& v, int key) {
  v.push_back(key);
  ascend(v, v.size() - 1);
}

void removeRoot(std::vector<int>& v) {
  int vSize = v.size();
  if (vSize > 1) {
    switchPos(v, 0, vSize - 1);
    v.pop_back();
    descend(v, 0);
  }
}

void buildHeap(std::vector<int>& v) {
  for (int i = floor(v.size()/2) - 1; i >= 0; i--) descend(v, i);
}

void heapSort(std::vector<int>& v) {
  for (int i = v.size() - 1; i > 0; i--) {
    switchPos(v, 0, i);
    std::vector<int> temp(v.begin(), v.begin() + i);
    descend(temp, 0);
    std::copy(temp.begin(), temp.end(), v.begin());
  }
}

int main() {
  std::vector<int> tree; // vector<node> simplificado
  tree = {50, 48, 45, 29, 15, 35, 40, 27, 26, 14, 12, 33, 30, 37, 20, 21, 19, 25};

  // tree = {0, 1, 2 , 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16, 17} ;

  buildHeap(tree);

  printVector(tree);

  heapSort(tree);

  // alterPriority(tree, 15, 36);
  // insertOnHeap(tree, 47);

  printVector(tree);

  return 0;
}