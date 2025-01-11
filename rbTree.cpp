#include <iostream>

class node {
public:
    int key;
    char color; // 'R' para vermelho, 'N' para preto
    node *left, *right, *parent;

    node(int keyValue) {
        key = keyValue;
        color = 'R'; // Nós novos são sempre vermelhos inicialmente
        left = nullptr;
        right = nullptr;
        parent = nullptr;
    }
};

class RedBlackTree {
private:
    node *root;

    void leftRotate(node *&root, node *&pt) {
        node *temp = pt->right;
        pt->right = temp->left;

        if (pt->right != nullptr)
            pt->right->parent = pt;

        temp->parent = pt->parent;

        if (pt->parent == nullptr)
            root = temp;
        else if (pt == pt->parent->left)
            pt->parent->left = temp;
        else
            pt->parent->right = temp;

        temp->left = pt;
        pt->parent = temp;
    }

    void rightRotate(node *&root, node *&pt) {
        node *temp = pt->left;
        pt->left = temp->right;

        if (pt->left != nullptr)
            pt->left->parent = pt;

        temp->parent = pt->parent;

        if (pt->parent == nullptr)
            root = temp;
        else if (pt == pt->parent->left)
            pt->parent->left = temp;
        else
            pt->parent->right = temp;

        temp->right = pt;
        pt->parent = temp;
    }

    void fixInsert(node *&root, node *&pt) {
        node *parent = nullptr;
        node *grandparent = nullptr;

        while (pt != root && pt->color == 'R' && pt->parent->color == 'R') {
            parent = pt->parent;
            grandparent = parent->parent;

            if (parent == grandparent->left) {
                node *uncle = grandparent->right;

                if (uncle != nullptr && uncle->color == 'R') {
                    grandparent->color = 'R';
                    parent->color = 'N';
                    uncle->color = 'N';
                    pt = grandparent;
                } else {
                    if (pt == parent->right) {
                        leftRotate(root, parent);
                        pt = parent;
                        parent = pt->parent;
                    }

                    rightRotate(root, grandparent);
                    std::swap(parent->color, grandparent->color);
                    pt = parent;
                }
            } else {
                node *uncle = grandparent->left;

                if (uncle != nullptr && uncle->color == 'R') {
                    grandparent->color = 'R';
                    parent->color = 'N';
                    uncle->color = 'N';
                    pt = grandparent;
                } else {
                    if (pt == parent->left) {
                        rightRotate(root, parent);
                        pt = parent;
                        parent = pt->parent;
                    }

                    leftRotate(root, grandparent);
                    std::swap(parent->color, grandparent->color);
                    pt = parent;
                }
            }
        }

        root->color = 'N';
    }

    void inorderTraversal(node *node) const {
        if (node == nullptr)
            return;

        inorderTraversal(node->left);
        std::cout << node->key << " (" << node->color << ") ";
        inorderTraversal(node->right);
    }

public:
    node* getRoot() {
        return root;
    }

    RedBlackTree() : root(nullptr) {}

    void insert(int key) {
        node *newNode = new node(key);
        root = bstInsert(root, newNode);
        fixInsert(root, newNode);
    }

    node* bstInsert(node* root, node* pt) {
        if (root == nullptr)
            return pt;

        if (pt->key < root->key) {
            root->left = bstInsert(root->left, pt);
            root->left->parent = root;
        } else if (pt->key > root->key) {
            root->right = bstInsert(root->right, pt);
            root->right->parent = root;
        }

        return root;
    }

    void displayInOrder() const {
        inorderTraversal(root);
    }

    ~RedBlackTree() {
        deleteTree(root);
    }

private:
    void deleteTree(node *node) {
        if (node == nullptr)
            return;

        deleteTree(node->left);
        deleteTree(node->right);
        delete node;
    }
};

node *getNode(node *root, int key) {
  if (root == nullptr || root->key == key) return root;
  if (root->key > key) return getNode(root->left, key);
  else if (root->key < key) return getNode (root->right, key);
  return root;
}

int main(void) {
    RedBlackTree tree;

    tree.insert(50);
    tree.insert(25);
    tree.insert(75);
    tree.insert(15);
    tree.insert(35);
    tree.insert(60);
    tree.insert(120);
    tree.insert(10);
    tree.insert(68);
    tree.insert(90);
    tree.insert(125);

    std::cout << "\n\n";
    tree.displayInOrder();
    std::cout << "\n" << std::endl;

    int valor;
    std::cout << "Digite um valor a ser encontrado na árvore: ";
    std::cin >> valor;

    std::cout << "Procurando " << valor << ": ";
    if (getNode(tree.getRoot(), valor) != nullptr) {
        std::cout << "Valor encontrado" << std::endl;
    }
    else {
        std::cout << "Valor não pertence a árvore" << std::endl;
    }

    return 0;
}
