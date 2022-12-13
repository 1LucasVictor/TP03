#ifndef AVLTREE
#define AVLTREE
#include <string>

#include "Palavra.hpp"
using namespace std;
#define keyType string
#define itemType Verbete

class Node {
 public:
  Node();
  itemType item;
  int balance;

  Node* right;
  Node* left;
  Node* parent;
};

class AVL_Tree {
 public:
  AVL_Tree();
  ~AVL_Tree();

  // Insert the item.
  void insert(itemType item);
  // Remove the item.
  void remove(keyType key, string type);
  // Modes: (0) pre-order; (1) in-order; (2) pos-order; (3) level-order.
  void print(int mode);
  // Search the the key.
  itemType search(keyType key, string type);
  // Clean the tree.
  void clean();

 private:
  void recursiveInsert(Node*& n, Node* parent, itemType item);
  void recursiveRemove(Node*& n, const keyType key, string type);
  itemType recursiveSearch(Node* n, keyType key, string type);
  void recursiveClean(Node* n);
  void levelOrder();
  void preOrder(Node* n);
  void inOrder(Node* n);
  void posOrder(Node* n);

  // Get node height.
  int height(Node* n);
  // Get Balance Factor.
  int balanceFactor(Node* n);
  // Get the antecessor.
  void antecessor(Node* q, Node*& r);
  void balance(Node* n);

  Node* leftRotation(Node* n);
  Node* rightRotation(Node* n);
  Node* left_right_Rotation(Node* n);
  Node* right_left_Rotation(Node* n);
  Node* root;
};

#endif