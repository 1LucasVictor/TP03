#include <iostream>
#include "AVLTree.hpp"
using namespace std;

int main() {
  AVL_Tree tree;

  tree.insert({3,3});
  tree.insert({20,20});
  tree.insert({10,10});  
  tree.insert({1,1});
  tree.insert({0,0});
  tree.insert({7,7});;
  tree.insert({18,18});
  tree.insert({21,21});
  tree.insert({25,25});
  tree.insert({0,0});
  tree.insert({22,22});
  tree.insert({30,30});
  
  tree.walk(0);
  tree.walk(1);
  tree.walk(2);
  tree.walk(3);

  tree.remove(1);
  tree.remove(0);
  tree.remove(20);
  tree.remove(22);

  // cout << "Nova arvore:\n";
  tree.walk(0);
  tree.walk(1);
  tree.walk(2);
  tree.walk(3);

  return 0;
}