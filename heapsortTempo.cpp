#include <iostream>
#include <vector>
#include <cmath>
#include <fstream>
#include <chrono>

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
    //captura o tempo de início
    auto start = std::chrono::high_resolution_clock::now();

    std::string fileName = "./lista_1000000.txt";
    std::ifstream list;
    list.open(fileName, std::ios::in);

    if (!list.is_open())
        return 1;  

    std::vector<int> tree;
    std::string line;
    while (std::getline(list, line)) {
        tree.push_back(std::stoi(line));
    }

    buildHeap(tree);

    heapSort(tree);

    // Captura o tempo de término
    auto end = std::chrono::high_resolution_clock::now();

    // Calcula a duração em milissegundos
    std::chrono::duration<double, std::micro> duration = end - start;

    // Exibe o tempo de execução
    std::cout << "O código levou " << duration.count() << " microssegundos para rodar." << std::endl;

    return 0;
}