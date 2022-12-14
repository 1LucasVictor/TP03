#ifndef AVLTREE
#define AVLTREE
#include <string>

#include "Palavra.hpp"
#include "Dictionary.hpp"
using namespace std;
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

class AVL_Tree : public Dictionary {
 public:
  AVL_Tree();
  ~AVL_Tree();

  // Insert the item.
  void insert(itemType item);
  // Remove the item.
  void remove(string key, string type);
  // Modes: (0) pre-order; (1) in-order; (2) pos-order; (3) level-order.
  // void print(int mode);
  void print(std::fstream& out);
  // Search the the key.
  itemType search(string key,  std::string type);
  // Clean the tree.
  void clean();
  // Removes all words with meaning
  void remove_all_with_mean();

 private:
  void recursiveInsert(Node*& n, Node* parent, itemType item);
  void recursiveRemove(Node*& n, const string key, string type);
  itemType recursiveSearch(Node* n, string key, string type);
  void recursiveClean(Node* n);
  // void levelOrder();
  // void preOrder(Node* n);
  void inOrder(Node* n, std::fstream& out);
  // void posOrder(Node* n);

  // Get node height.
  int height(Node* n);
  // Get Balance Factor.
  int balanceFactor(Node* n);
  // Get the antecessor.
  void antecessor(Node* q, Node*& r);
  void balance(Node* n);
  //// Return a list of all Verbetes in the tree
  void getList(Node* r, Verbete* v, int& n);
  // Contains the size of the tree
  int size;
  Node* leftRotation(Node* n);
  Node* rightRotation(Node* n);
  Node* left_right_Rotation(Node* n);
  Node* right_left_Rotation(Node* n);
  Node* root;
};

#endif