#include "AVLTree.hpp"

#include <iostream>

struct lCell {
  Node *item;
  lCell *next;
};

class levelQueue{
  public: 
    levelQueue() {
      first = nullptr;
      last = first;
      length = 0;
    }

    void insert(Node *n) {
      length++;
      if(first == nullptr) {
        first = new lCell{n, nullptr};
        last = first;
        return;
      }
      last->next = new lCell{n, nullptr};
      last = last->next;
    }

    Node* remove() {
      Node *aux;
      if(length == 0)
        return nullptr;
      aux = first->item;
      first = first->next;
      length--;
      return aux;
    }

    int length;
  private:
    lCell *first;
    lCell *last;
};

Node::Node() {
  height = 1;
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

void AVL_Tree::recursiveInsert(Node*& n, Node* parent, itemType item) {
  if (n == nullptr) {
    n = new Node();
    n->item = item;
    n->height = 1;
    n->parent = parent;


    // Updating balance factors
    auto temp = parent;
    while (temp != nullptr) {
      temp->height++;
      temp->balance = balanceFactor(temp);
      temp = temp->parent;
    }

    // Rotations
    // if(height(n) >= 2) {
    //   if ((n->parent->left == n) && n->parent->parent->balance < -1)
    //     this->rightRotation(n->parent);
    //   else if ((n->parent->right == n) && n->parent->parent->balance > 1)
    //     this->leftRotation(n->parent);
    //   else if ((n->parent->right == n) && n->parent->parent->balance < -1) {
    //     this->leftRotation(n->parent);
    //     this->rightRotation(n);
    //   } else if ((n->parent->left == n) && n->parent->parent->balance > 1) {
    //     this->rightRotation(n->parent);
    //     this->leftRotation(n);
    //   }
    // }

    // Updating balance factors
    while (temp != nullptr) {
      temp->height++;
      temp->balance = balanceFactor(temp);
      temp = temp->parent;
    }
  } else {
    if (item.key < n->item.key)
      recursiveInsert(n->left, n, item);
    else
      recursiveInsert(n->right, n, item);
  }
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

void AVL_Tree::recursiveRemove(Node*& n, keyType key) {
  if (n == nullptr)
    return;
  if (key > n->item.key)
    recursiveRemove(n->right, key);
  else if (key < n->item.key)
    recursiveRemove(n->left, key);
  else {
    auto temp = n;
    if (n->right == nullptr) {
      n = n->left;
    } else if (n->left == nullptr) {
      n = n->right;
    } else {
      antecessor(n, n->left);
    }
    // Updating balance factors
    auto aux = temp->parent;
    while (aux != nullptr) {
      aux->height--;
      aux->balance = balanceFactor(aux);
      aux = aux->parent;
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
  Node *p;

  q.insert(root);
  while(q.length) {
    p = q.remove();
    if(p != nullptr) {
      std::cout << p->item.value << ' ';
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

void AVL_Tree::rightRotation(Node* n) {
  auto y = n->left;
  n->left = y->right;
  if (y->right != nullptr) {
    y->right->parent = n;
  }
  n->parent = y->parent;
  if (n->parent == nullptr) {
    this->root = y;
  } else if (n == n->parent->right) {
    n->parent->right = y;
  } else {
    n->parent->left = y;
  }
  y->right = n;
  n->parent = y;

  n->balance = n->balance + 1 - std::min(0, y->balance);
  y->balance = y->balance + 1 + std::max(0, n->balance);
}
