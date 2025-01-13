#include <iostream>
#include <queue>
#include <vector>
#include <bits/stdc++.h>
#include <cmath>

struct node {
  int key;
  node *left;
  node *right;
  typedef struct node knot;
};

void freeMemory(node *&root) {
  if (root == NULL) return;

  freeMemory(root->left);
  freeMemory(root->right);

  delete[] root;
}

void printPreOrder(node *root) {
  if (root == NULL) return;
  std::cout << root->key << " ";
  printPreOrder(root->left);
  printPreOrder(root->right);
}

void printInOrder(node *root) {
  if (root == NULL) return;
  printInOrder(root->left);
  std::cout << root->key << " ";
  printInOrder(root->right);
}

void printPostOrder(node *root) {
  if (root == NULL) return;
  printPostOrder(root->left);
  printPostOrder(root->right);
  std::cout << root->key << " ";
}

void printInLevel(node *root) {
  if (root == NULL) return;

  std::queue<node*> q;
  q.push(root);

  while (!q.empty()) {
    node *current = q.front(); // Pegamos o primeiro nó da fila
    q.pop();                   // Removemos o nó da fila

    // Imprimimos o valor do nó atual
    std::cout << current->key << " ";

    // Enfileiramos o filho da esquerda, se existir
    if (current->left != nullptr) {
        q.push(current->left);
    }

    // Enfileiramos o filho da direita, se existir
    if (current->right != nullptr) {
        q.push(current->right);
    }
  }
}

node *getNode(node *root, int key) {
  if (root == NULL || root->key == key) return root;
  if (root->key > key) return getNode(root->left, key);
  else if (root->key < key) return getNode (root->right, key);
  return root;
}

node *insertNode(node *root, int key) {
  if (root == NULL) {
    node *newNode = (node*) malloc(sizeof(node));
    newNode->key = key;
    newNode->left = newNode->right = NULL;
    return newNode;
  }
  if (key < root->key) root->left = insertNode(root->left, key);
  else if(key > root->key) root->right = insertNode(root->right, key);
  return root;
}

node *removeNode(node *root, int key) {
  if (root == NULL) return NULL;
  if (root->key == key) {
    if (root->left == NULL && root->right == NULL) {
      // std::cout << "sal";
      // std::cout << std::endl;
      return NULL;
    } else if (root->left != NULL && root->right != NULL) {
      node *biggestLeftNode = root->left;
      node *biggestFather = root;
      while (biggestLeftNode->right != NULL) {
        biggestFather = biggestLeftNode;
        biggestLeftNode = biggestLeftNode->right;
      }

      int temp = root->key;
      root->key = biggestLeftNode->key;
      biggestLeftNode->key = temp;

      biggestFather->right = removeNode(biggestLeftNode, biggestLeftNode->key);
      return root;
    } else if (root->left != NULL) {
      // std::cout << "salve3";
      // std::cout << std::endl;
      return root->left;
    } else if (root->right != NULL) {
      // std::cout << "salve4";
      // std::cout << std::endl;
      return root->right;
    }
  }
  if (key < root->key) root->left = removeNode(root->left, key);
  if (key > root->key) root->right = removeNode(root->right, key);
  return root;
}

node *createTree(std::vector<int> array, bool firstCall=true){
  if (array.empty()) return NULL;
  std::vector<int> leftVec;
  std::vector<int> rightVec;
  if (firstCall) sort(array.begin(), array.end());

  int middleIndex = floor(array.size()/2);
  leftVec = std::vector<int>(array.begin(), array.begin() + middleIndex);
  rightVec = std::vector<int>(array.begin() + middleIndex + 1, array.end());

  node *root = NULL;
  root = insertNode(root, array[middleIndex]);

  root->left = createTree(leftVec, false);
  root->right = createTree(rightVec, false);

  return root;
}

int main() {
  std::vector<int> teste{1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11};

  node *root = createTree(teste);

  printInLevel(root);
  std::cout << std::endl;

  removeNode(root, 6);

  printInLevel(root);
  std::cout << std::endl;

  freeMemory(root);

  return 0;
}