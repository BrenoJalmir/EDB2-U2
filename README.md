# Trabalho de EDB2 - Unidade II

## 1. Heap

### Ambiente computacional
* **Software**: VS Code
* **Sistema operacional**: Windows 10
* **Processador**: Ryzen 7 5700X3D
* **Memória ram**: 32 GB
* **Placa de vídeo**: RTX 3050

### Funções heap

* Heap máximo
<details>
  <summary>Clique aqui para ver o código</summary>

  Implementação das funções de heap máximo, incluindo o Heapsort.

    ```c++
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
    ```

</details>

* Heap mínimo
<details>
  <summary>Clique aqui para ver o código</summary>

  Implementação das funções de heap mínimo, incluindo o Heapsort.

  ```c++
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
        buildHeap(v); // Certifique-se de que o heap mínimo está construído
    
        for (int i = v.size() - 1; i > 0; i--) {
            switchPos(v, 0, i);    // Troca o menor elemento (raiz) com o último elemento
            descend(v, 0);         // Ajusta o heap para o restante do vetor
        }
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
    
        // // Alteração de prioridade
        // alterPriority(tree, 15, 5);
        // std::cout << "Heap após alteração de prioridade: ";
        // printVector(tree);
    
        // // Inserção de um novo elemento
        // insertOnHeap(tree, 10);
        // std::cout << "Heap após inserção: ";
        // printVector(tree);
    
        // // Remoção da raiz
        // removeRoot(tree);
        // std::cout << "Heap após remoção da raiz: ";
        // printVector(tree);
    
        // Ordenação do Heap
        heapSort(tree);
        std::cout << "Heap ordenado: ";
        printVector(tree);
    
        return 0;
    }
  ```
  
</details>

* Pseudocódico do Heapsort
<details>
  <summary>Clique aqui para ver o pseudocódigo</summary>


  ```
    FUNÇÃO principal
    DECLARE tree COMO vetor de inteiros
    tree <- {50, 48, 45, 29, 15, 35, 40, 27, 26, 14, 12, 33, 30, 37, 20, 21, 19, 25}

    CHAME buildHeap(tree)
    CHAME printVector(tree)
    CHAME heapSort(tree)
    CHAME printVector(tree)

    FIM FUNÇÃO
    
    FUNÇÃO printVector(vetor v)
        PARA i DE 0 ATÉ tamanho(v) - 1 FAÇA
            IMPRIMA v[i]
        FIM PARA
    FIM FUNÇÃO
    
    FUNÇÃO switchPos(vetor v, inteiro index1, inteiro index2)
        temp <- v[index1]
        v[index1] <- v[index2]
        v[index2] <- temp
    FIM FUNÇÃO
    
    FUNÇÃO descend(vetor v, inteiro index)
        DECLARE biggerPriorityIndex COMO index
        vSize <- tamanho(v)
    
        SE 2 * index + 1 < vSize E v[2 * index + 1] > v[biggerPriorityIndex] ENTÃO
            biggerPriorityIndex <- 2 * index + 1
        FIM SE
    
        SE 2 * index + 2 < vSize E v[2 * index + 2] > v[biggerPriorityIndex] ENTÃO
            biggerPriorityIndex <- 2 * index + 2
        FIM SE
    
        SE biggerPriorityIndex != index ENTÃO
            CHAME switchPos(v, index, biggerPriorityIndex)
            CHAME descend(v, biggerPriorityIndex)
        FIM SE
    FIM FUNÇÃO
    
    FUNÇÃO ascend(vetor v, inteiro index)
        father <- (index - 1) DIV 2
        SE v[index] > v[father] ENTÃO
            CHAME switchPos(v, index, father)
            CHAME ascend(v, father)
        FIM SE
    FIM FUNÇÃO
    
    FUNÇÃO alterPriority(vetor v, inteiro index, inteiro newPriority)
        SE v[index] >= newPriority ENTÃO
            action <- descend
        SENÃO
            action <- ascend
        FIM SE
        v[index] <- newPriority
        CHAME action(v, index)
    FIM FUNÇÃO
    
    FUNÇÃO insertOnHeap(vetor v, inteiro key)
        ADICIONE key AO FINAL DE v
        CHAME ascend(v, tamanho(v) - 1)
    FIM FUNÇÃO
    
    FUNÇÃO removeRoot(vetor v)
        SE tamanho(v) > 1 ENTÃO
            CHAME switchPos(v, 0, tamanho(v) - 1)
            REMOVA O ÚLTIMO ELEMENTO DE v
            CHAME descend(v, 0)
        FIM SE
    FIM FUNÇÃO
    
    FUNÇÃO buildHeap(vetor v)
        PARA i DE (tamanho(v) DIV 2) - 1 ATÉ 0 PASSO -1 FAÇA
            CHAME descend(v, i)
        FIM PARA
    FIM FUNÇÃO
    
    FUNÇÃO heapSort(vetor v)
        PARA i DE tamanho(v) - 1 ATÉ 1 PASSO -1 FAÇA
            CHAME switchPos(v, 0, i)
            temp <- SUBVETOR DE v DE 0 ATÉ i
            CHAME descend(temp, 0)
            COPIE temp PARA OS PRIMEIROS ELEMENTOS DE v
        FIM PARA
    FIM FUNÇÃO

  ```
  
</details>

### Comparando resultados

Alguns códigos não funcionaram para as listas de tamanho 1000000, e por isso tiveram que ser removidos do gráfico. Para melhor visualização, separamos as análises em 3 gráficos diferentes, mantendo assim uma escala mais compreensível. O eixo X de cada gráfico representa os diferentes algoritmos utilizados, enquanto que o eixo y representa o tempo em segundos que cada algoritmo levou para ser executado.

**Gráfico comparando o desempenho dos algoritmos ao ordenar uma lista com 10000 elementos**

![Graph10000](https://i.ibb.co/rZhzdFh/Sorts-10000.png)

**Gráfico comparando o desempenho dos algoritmos ao ordenar uma lista com 10000 elementos**

![Graph100000](https://i.ibb.co/Y8G0xqv/Sorts-100000.png)

**Gráfico comparando o desempenho dos algoritmos ao ordenar uma lista com 10000 elementos**

![Graph1000000](https://i.ibb.co/yy7f64W/Sorts-1000000.png)