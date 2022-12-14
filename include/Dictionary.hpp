#ifndef DICTIONARY
#define DICTIONARY
#include <iostream>
#include <fstream>
#include "Palavra.hpp"


class Dictionary {
 public:
  Dictionary() {
    this->M = 0;
  }
  Dictionary(int len) {
    this->M = len;
  }
  virtual Verbete search(std::string key, std::string type){
    Verbete aux;
    return aux;
  }
  virtual void insert(Verbete it){}
  virtual void print(std::fstream& out){}
  virtual void remove(std::string key, std::string type){}
  virtual void remove_all_with_mean(){}
  // void atualizaDic(Verbete it);
  int M;
};

#endif