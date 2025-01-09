#include <iostream>

class node {
    public:
    int key;
    int h; // height
    char color;
    node *left;
    node *right;

    node(int key, int h) {
        this->left = nullptr;
        this->right = nullptr;

        this->key = key;
        this->h = h;
        this->color = 'R';
    };
};

void freeMemory(node *&root) {
  if (root == NULL) return;

  freeMemory(root->left);
  freeMemory(root->right);

  delete[] root;
}

void printPreOrder(node *root) {
  if (root == NULL) return;
  std::cout << root->key;
  printPreOrder(root->left);
  printPreOrder(root->right);
}

void printInOrder(node *root) {
  if (root == NULL) return;
  printInOrder(root->left);
  std::cout << root->key;
  printInOrder(root->right);
}

void printPostOrder(node *root) {
  if (root == NULL) return;
  printPostOrder(root->left);
  printPostOrder(root->right);
  std::cout << root->key;
}

node *getNode(node *root, int key) {
  if (root == NULL || root->key == key) return root;
  if (root->key > key) return getNode(root->left, key);
  else if (root->key < key) return getNode (root->right, key);
  return root;
}

node *copyNode(node *toCopy) {
  node *newNode = new node(toCopy->key, toCopy->h);
  newNode->left = toCopy->left;
  newNode->right = toCopy->right;
  return newNode;
}

int calcHeight(node *root) {
  int leftH = 0;
  int rightH = 0;

  if (root->left != NULL) leftH = root->left->h;
  if (root->right != NULL) rightH = root->right->h;

  return 1 + std::max(leftH, rightH);
}

void rotateLeft(node *&root) {
  if (root == NULL) return;
  if (root->right == NULL) return;
  if (root->right->left == NULL) {
    root->right->left = copyNode(root);
    root->right->left->right = NULL;
    root = root->right;
    root->left->h = calcHeight(root->left);
  } else {
    node *temp = root->right->left; 
    root->right->left = copyNode(root);
    root->right->left->right = temp;
    root = root->right;
    root->left->h = calcHeight(root->left);
    root->left->right->h = calcHeight(root->left->right);
    root->h = calcHeight(root);
  }
}

void rotateRight(node *&root) {
  if (root == NULL) return;
  if (root->left == NULL) return;
  if (root->left->right == NULL) {
    root->left->right = copyNode(root);
    root->left->right->left = NULL;
    root = root->left;
    root->right->h = calcHeight(root->right);
  } else {
    node *temp = root->left->right;
    root->left->right = copyNode(root);
    root->left->right->left = temp;
    root = root->left;
    root->right->h = calcHeight(root->right);
    root->right->left->h = calcHeight(root->right->left);
    root->h = calcHeight(root);
  }
}

int calcBalancing(node *root) {
  int leftH = 0;
  int rightH = 0;

  if (root->left != NULL) leftH = root->left->h;
  if (root->right != NULL) rightH = root->right->h;

  return leftH - rightH;
}

void insertNode(node *&root, int key) {
  if (root == NULL) {
    node *newNode = new node(key, 1);
    newNode->left = newNode->right = NULL;
    root = newNode;
    return;
  }

  if (key < root->key) insertNode(root->left, key);
  else if(key > root->key) insertNode(root->right, key);

  root->h = calcHeight(root);
  int bl = calcBalancing(root);

  if (bl > 1 && key < root->left->key) {
    rotateRight(root);
    return;
  }
  if (bl > 1 && key > root->left->key) {
    rotateLeft(root->left);
    rotateRight(root);
    return;
  }
  if (bl < -1 && key > root->right->key) {
    rotateLeft(root);
    return;
  }
  if (bl < -1 && key < root->right->key) {
    rotateRight(root->right);
    rotateLeft(root);
    return;
  }
}

void removeNode(node *&root, int key) {
  if (root == NULL) return;

  if (root->key == key) {
    if (root->left == NULL && root->right == NULL) {
      root = NULL;
      return;
    } else if (root->left != NULL && root->right != NULL) {
        node *greaterLeftNode = root->left;

      while (greaterLeftNode->right != NULL) greaterLeftNode = greaterLeftNode->right;

      int temp = root->key;
      root->key = greaterLeftNode->key;
      greaterLeftNode->key = temp;

      removeNode(root->left, greaterLeftNode->key);
      // node *lesserRightNode = root->right;

      // while (lesserRightNode->left != NULL) lesserRightNode = lesserRightNode->left;

      // int temp = root->key;
      // root->key = lesserRightNode->key;
      // lesserRightNode->key = temp;

      // removeNode(root->right, lesserRightNode->key);
      // return;
    } else if (root->left != NULL) {
      root = root->left;
      return;
    } else if (root->right != NULL) {
      root = root->right;
      return;
    }
  }
  
  if (key < root->key) removeNode(root->left, key);
  if (key > root->key) removeNode(root->right, key);

  root->h = calcHeight(root);
  int bl = calcBalancing(root);

  if (bl > 1 && root->left != NULL && calcBalancing(root->left) >= 0) {
    rotateRight(root);
    return;
  }
  if (bl > 1 && root->left != NULL && calcBalancing(root->left) < 0) {
    rotateLeft(root->left);
    rotateRight(root);
    return;
  }

  if(bl < -1 && root->right != NULL && calcBalancing(root->right) <= 0) {
    rotateLeft(root);
    return;
  }
  if(bl < -1 && root->right != NULL && calcBalancing(root->right) > 0) {
    rotateRight(root->right);
    rotateLeft(root);
    return;
  }
}

int main () {
  node *tree = NULL;
  insertNode(tree, 50);
  insertNode(tree, 25);
  insertNode(tree, 75);
  insertNode(tree, 15);
  insertNode(tree, 35);
  insertNode(tree, 60);
  insertNode(tree, 120);
  insertNode(tree, 10);
  insertNode(tree, 68);
  insertNode(tree, 90);
  insertNode(tree, 125);
  insertNode(tree, 83);
  insertNode(tree, 99);

  printPreOrder(tree);
  printf("\n\n");

  removeNode(tree, 120);

  printPreOrder(tree);
  printf("\n\n");

  freeMemory(tree);

  return 0;
}