#include "AVLTree.hpp"

#include <iostream>

struct lCell {
  Node* item;
  lCell* next;
};

class levelQueue {
 public:
  levelQueue() {
    first = nullptr;
    last = first;
    length = 0;
  }

  void insert(Node* n) {
    length++;
    if (first == nullptr) {
      first = new lCell{n, nullptr};
      last = first;
      return;
    }
    last->next = new lCell{n, nullptr};
    last = last->next;
  }

  Node* remove() {
    Node* aux;
    if (length == 0)
      return nullptr;
    aux = first->item;
    first = first->next;
    length--;
    return aux;
  }

  int length;

 private:
  lCell* first;
  lCell* last;
};

Node::Node() {
  right = nullptr;
  left = nullptr;
  parent = nullptr;
  balance = 0;
}

AVL_Tree::AVL_Tree() {
  root = nullptr;
}
void AVL_Tree::insert(itemType item) {
  recursiveInsert(this->root, nullptr, item);
}

void AVL_Tree::remove(keyType key) {
  recursiveRemove(root, key);
}

void AVL_Tree::walk(int mode) {
  if (mode == 0)
    preOrder(root);
  else if (mode == 1)
    inOrder(root);
  else if (mode == 2)
    posOrder(root);
  else
    levelOrder();

  std::cout << '\n';
}

itemType AVL_Tree::search(keyType key) {
  return recursiveSearch(root, key);
}

void AVL_Tree::clean() {
  recursiveClean(root);
}

int AVL_Tree::height(Node* n) {
  if (n == nullptr)
    return 0;
  return 1 + std::max(height(n->left), height(n->right));
}

int AVL_Tree::balanceFactor(Node* n) {
  if (n == nullptr)
    return 0;
  return this->height(n->right) - this->height(n->left);
}

void AVL_Tree::recursiveInsert(Node*& r, Node* parent, itemType item) {
  if (r == NULL) {
    r = new Node;
    r->parent = parent;
    r->item = item;
  } else {
    Node* n = r;
    Node* parent;

    while (true) {
      if (n->item.key == item.key)
        return;

      parent = n;

      bool goLeft = n->item.key > item.key;
      n = goLeft ? n->left : n->right;

      if (n == NULL) {
        if (goLeft) {
          parent->left = new Node();
          parent->left->item = item;
          parent->left->parent = parent;
        } else {
          parent->right = new Node();
          parent->right->item = item;
          parent->right->parent = parent;
        }
        balance(parent);
        break;
      }
    }
  }
  return;
}

void AVL_Tree::antecessor(Node* q, Node*& r) {
  if (r->right != nullptr) {
    antecessor(q, r->right);
    return;
  }
  q->item = r->item;
  q = r;
  r = r->left;
}

void AVL_Tree::recursiveRemove(Node*& r, const keyType key) {
  if (root == nullptr)
    return;

  Node
      *n = root,
      *parent = root,
      *delNode = nullptr,
      *child = root;

  while (child != nullptr) {
    parent = n;
    n = child;
    child = key >= n->item.key ? n->right : n->left;
    if (key == n->item.key) {
      delNode = n;
    }
  }

  if (delNode != nullptr) {
    delNode->item = n->item;
    child = n->left != nullptr ? n->left : n->right;

    if (root->item.key == key) {
      root = child;
    } else {
      if (parent->left == n) {
        parent->left = child;
      } else {
        parent->right = child;
      }

      balance(parent);
    }
  }
}

itemType AVL_Tree::recursiveSearch(Node* n, keyType key) {
  if (n == nullptr) {
    itemType temp;
    temp.key = -1;
    return temp;
  }

  if (key > n->item.key)
    return recursiveSearch(n->right, key);
  else if (key < n->item.key)
    return recursiveSearch(n->left, key);
  else
    return n->item;
}

void AVL_Tree::recursiveClean(Node* n) {
  if (n == nullptr)
    return;
  recursiveClean(n->left);
  recursiveClean(n->right);
  delete n;
}

void AVL_Tree::levelOrder() {
  levelQueue q;
  Node* p;

  q.insert(root);
  while (q.length) {
    p = q.remove();
    if (p != nullptr) {
      std::cout <<  p->item.value << ' ';
      q.insert(p->left);
      q.insert(p->right);
    }
  }
}

void AVL_Tree::preOrder(Node* n) {
  if (n == nullptr)
    return;
  std::cout << n->item.value << ' ';
  preOrder(n->left);
  preOrder(n->right);
}
void AVL_Tree::inOrder(Node* n) {
  if (n == nullptr)
    return;
  inOrder(n->left);
  std::cout << n->item.value << ' ';
  inOrder(n->right);
}

void AVL_Tree::posOrder(Node* n) {
  if (n == nullptr)
    return;
  posOrder(n->left);
  posOrder(n->right);
  std::cout << n->item.value << ' ';
}

Node* AVL_Tree::leftRotation(Node* n) {
  Node* rightChild = n->right;
  rightChild->parent = n->parent;
  n->right = rightChild->left;

  if (n->right != NULL)
    n->right->parent = n;

  rightChild->left = n;
  n->parent = rightChild;

  if (rightChild->parent != NULL) {
    if (rightChild->parent->right == n) {
      rightChild->parent->right = rightChild;
    } else {
      rightChild->parent->left = rightChild;
    }
  }

  n->balance = balanceFactor(n);
  rightChild->balance = balanceFactor(rightChild);
  return rightChild;
}

Node* AVL_Tree::rightRotation(Node* n) {
  Node* leftChild = n->left;
  leftChild->parent = n->parent;
  n->left = leftChild->right;

  if (n->left != NULL)
    n->left->parent = n;

  leftChild->right = n;
  n->parent = leftChild;

  if (leftChild->parent != NULL) {
    if (leftChild->parent->right == n) {
      leftChild->parent->right = leftChild;
    } else {
      leftChild->parent->left = leftChild;
    }
  }

  n->balance = balanceFactor(n);
  leftChild->balance = balanceFactor(leftChild);
  return leftChild;
}

Node* AVL_Tree::left_right_Rotation(Node* n) {
  n->left = leftRotation(n->left);
  return rightRotation(n);
}

Node* AVL_Tree::right_left_Rotation(Node* n) {
  n->right = rightRotation(n->right);
  return leftRotation(n);
}

void AVL_Tree::balance(Node* n) {
  n->balance = balanceFactor(n);
  if (n->balance == -2) {
    if (height(n->left->left) >= height(n->left->right))
      n = rightRotation(n);
    else
      n = left_right_Rotation(n);
  } else if (n->balance == 2) {
    if (height(n->right->right) >= height(n->right->left))
      n = leftRotation(n);
    else
      n = right_left_Rotation(n);
  }

  if (n->parent != NULL) {
    balance(n->parent);
  } else {
    root = n;
  }
}

AVL_Tree::~AVL_Tree() {
  clean();
}