#include <iostream>
#include <vector>
#include <cmath>
#include <algorithm>

struct node {
    int key;
    struct node *left;
    struct node *right;
    typedef struct node knot;
};

// Função para imprimir o vetor
void printVector(std::vector<int> v) {
    for (int i = 0; i < v.size(); i++) {
        std::cout << v[i] << " ";
    }
    std::cout << std::endl;
}

// Troca de posições no vetor
void switchPos(std::vector<int>& v, int index1, int index2) {
    int temp = v[index1];
    v[index1] = v[index2];
    v[index2] = temp;
}

// Ajusta o heap para baixo (descend)
void descend(std::vector<int>& v, int index) {
    int smallestPriorityIndex = index;
    int vSize = v.size();

    if (index * 2 + 1 < vSize && v[2 * index + 1] < v[smallestPriorityIndex])
        smallestPriorityIndex = 2 * index + 1;

    if (index * 2 + 2 < vSize && v[2 * index + 2] < v[smallestPriorityIndex])
        smallestPriorityIndex = 2 * index + 2;

    if (smallestPriorityIndex != index) {
        switchPos(v, index, smallestPriorityIndex);
        descend(v, smallestPriorityIndex);
    }
}

// Ajusta o heap para cima (ascend)
void ascend(std::vector<int>& v, int index) {
    int father = floor((index - 1) / 2);
    if (index > 0 && v[index] < v[father]) {
        switchPos(v, index, father);
        ascend(v, father);
    }
}

// Altera a prioridade de um elemento no heap
void alterPriority(std::vector<int>& v, int index, int newPriority) {
    void (*action)(std::vector<int>&, int);
    if (v[index] <= newPriority)
        action = descend;
    else
        action = ascend;

    v[index] = newPriority;
    action(v, index);
}

// Insere um elemento no heap
void insertOnHeap(std::vector<int>& v, int key) {
    v.push_back(key);
    ascend(v, v.size() - 1);
}

// Remove a raiz (mínimo) do heap
void removeRoot(std::vector<int>& v) {
    int vSize = v.size();
    if (vSize > 1) {
        switchPos(v, 0, vSize - 1);
        v.pop_back();
        descend(v, 0);
    } else if (vSize == 1) {
        v.pop_back();
    }
}

// Constrói o heap a partir de um vetor desordenado
void buildHeap(std::vector<int>& v) {
    for (int i = floor(v.size() / 2) - 1; i >= 0; i--) {
        descend(v, i);
    }
}

// Ordena o vetor usando HeapSort
void heapSort(std::vector<int>& v) {
    std::vector<int> temp = v;
    std::vector<int> sorted;

    // Extrair os menores elementos e construir o vetor crescente
    while (!temp.empty()) {
        sorted.push_back(temp.front());
        removeRoot(temp);
    }

    // Inverter o vetor para obter a ordem decrescente
    std::reverse(sorted.begin(), sorted.end());

    // Substituir o vetor original pelo vetor ordenado
    v = sorted;
}


int main() {
    std::vector<int> tree;

    // Exemplo de entrada
    tree = {50, 48, 45, 29, 15, 35, 40, 27, 26, 14, 12, 33, 30, 37, 20, 21, 19, 25};

    std::cout << "Vetor original: ";
    printVector(tree);

    // Construção do Heap
    buildHeap(tree);
    std::cout << "Heap mínimo construído: ";
    printVector(tree);

    // Alteração de prioridade
    alterPriority(tree, 15, 5);
    std::cout << "Heap após alteração de prioridade: ";
    printVector(tree);

    // Inserção de um novo elemento
    insertOnHeap(tree, 10);
    std::cout << "Heap após inserção: ";
    printVector(tree);

    // Remoção da raiz
    removeRoot(tree);
    std::cout << "Heap após remoção da raiz: ";
    printVector(tree);

    // Ordenação do Heap
    heapSort(tree);
    std::cout << "Heap ordenado: ";
    printVector(tree);

    return 0;
}