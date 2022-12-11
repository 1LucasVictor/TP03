#ifndef AVLTREE
#define AVLTREE

#define keyType int

struct itemType {
  keyType key;
  int value;
};

class Node {
  public:
    Node();
    itemType item;
    int height;
    int balance;

    Node* right;
    Node* left;
    Node* parent;
};

class AVL_Tree {
 public:
  AVL_Tree();
  ~AVL_Tree();

  void insert(itemType item);
  void remove(keyType key);
  void walk(int mode);
  itemType search(keyType key);
  void clean();

 private:
  void recursiveInsert(Node*& n, Node* parent, itemType item);
  void recursiveRemove(Node*& n, keyType key);
  itemType recursiveSearch(Node* n, keyType key);
  void recursiveClean(Node* n);
  void levelOrder();
  void preOrder(Node* n);
  void inOrder(Node* n);
  void posOrder(Node* n);
  
  int height(Node* n);
  int balanceFactor(Node* n);
  void antecessor(Node* q, Node*& r);
  void rightRotation(Node* n);
  void leftRotation(Node* n);
  Node* root;
};

#endif