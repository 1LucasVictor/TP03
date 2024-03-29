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
  size = 0;
}
void AVL_Tree::insert(itemType item) {
  recursiveInsert(this->root, nullptr, item);
}

void AVL_Tree::remove(string key, string type) {
  recursiveRemove(root, key, type);
}

// void AVL_Tree::print(int mode) {
//   if (mode == 0)
//     preOrder(root);
//   else if (mode == 1)
//     inOrder(root);
//   else if (mode == 2)
//     posOrder(root);
//   else
//     levelOrder();

//   std::cout << '\n';
// }

void AVL_Tree::print(std::fstream& out) {
    inOrder(root, out);
}

itemType AVL_Tree::search(string key, string type) {
  return recursiveSearch(root, key, type);
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
      if (n->item.verbete == item.verbete && n->item.type == item.type ) {
        
        n->item.setMean(item.significados[0]);
        return;
      }

      parent = n;
      
      bool goLeft = (n->item.verbete > item.verbete);
      if (n->item.verbete == item.verbete) {
        goLeft = (n->item.type > item.type);
      }
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
  size++;
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

void AVL_Tree::recursiveRemove(Node*& r, const string key, string type) {
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
    if(key > n->item.verbete)
      child = n->right;
    else if(key < n->item.verbete)
      child = n->left;
    else {
      if(type < n->item.type) child = n->left;
      else child = n->right;
    }
    // child = key >= n->item.verbete ? n->right : n->left;
    if (key == n->item.verbete && type == n->item.type) {
      delNode = n;
    }
  }

  if (delNode != nullptr) {
    size--;
    delNode->item = n->item;
    child = n->left != nullptr ? n->left : n->right;

    if (root->item.verbete == key) {
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

itemType AVL_Tree::recursiveSearch(Node* n, string key, string type) {
  if (n == nullptr) {
    itemType temp;
    temp.verbete = -1;
    return temp;
  }

  if (key > n->item.verbete)
    return recursiveSearch(n->right, key, type);
  else if (key < n->item.verbete)
    return recursiveSearch(n->left, key, type);
  else if(key == n->item.verbete && type > n->item.type)
    return recursiveSearch(n->right, key, type);
  else if(key == n->item.verbete && type < n->item.type)
    return recursiveSearch(n->left, key, type);
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

// void AVL_Tree::levelOrder() {
//   levelQueue q;
//   Node* p;

//   q.insert(root);
//   while (q.length) {
//     p = q.remove();
//     if (p != nullptr) {
//       p->item.print();
//       q.insert(p->left);
//       q.insert(p->right);
//     }
//   }
// }

// void AVL_Tree::preOrder(Node* n) {
//   if (n == nullptr)
//     return;
//   n->item.print();
//   preOrder(n->left);
//   preOrder(n->right);
// }
void AVL_Tree::inOrder(Node* n, std::fstream& out) {
  if (n == nullptr)
    return;
  inOrder(n->left, out);
  n->item.print(out);
  inOrder(n->right, out);
}

// void AVL_Tree::posOrder(Node* n) {
//   if (n == nullptr)
//     return;
//   posOrder(n->left);
//   posOrder(n->right);
//   n->item.print();
// }

void AVL_Tree::remove_all_with_mean() {
 Verbete *itens = new Verbete[size];
 int n = 0;
 getList(root, itens, n);
 for(int i = 0; i < n; i++) {
  if(itens[i].n) {
    remove(itens[i].verbete, itens[i].type);
  }
 }
}
void AVL_Tree::getList(Node* r, Verbete* v, int& n){
  if (r == nullptr)
    return;
  getList(r->left, v, n);
  getList(r->right, v, n);
  v[n] = r->item;
  n++;
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