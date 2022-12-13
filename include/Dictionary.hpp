#ifndef DICTIONARY
#define DICTIONARY
#include <iostream>
#include "AVLTree.hpp"
#include "Palavra.hpp"

template <class T>
class Dictionary {
 public:
  Dictionary(){}
	// void pesquisaDic(Verbete * it);
	void insereDic(Verbete it) {
		dict.insert(it);
	}
	void imprimeDic() {
		dict.walk(1);
	}
	// void atualizaDic(Verbete it);
	// void removeDic(Verbete it);
 private:
	T dict;
};

#endif