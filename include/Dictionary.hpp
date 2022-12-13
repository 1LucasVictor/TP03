#ifndef DICTIONARY
#define DICTIONARY
#include <iostream>

#include "Palavra.hpp"
#include "AVLTree.hpp"
#include "Hash_EA.hpp"


template <class T>
class Dictionary {
 public:
  Dictionary() {}
  Verbete pesquisaDic(string key, string type) {
    return dict.search(key, type);
  }
  void insereDic(Verbete it) {
    dict.insert(it);
  }
  void imprimeDic() {
    dict.print(1);
  }
  // void atualizaDic(Verbete it);
  // void removeDic(Verbete it);
 private:
  T dict;
};

#endif