#include "Hash_EA.hpp"

#include <iostream>

#include "SelectionSort.hpp"
using namespace std;

Hash_EA::Hash_EA(int len) {
  this->M = len;
  this->Table = new itemType[M];
  this->empty = new bool[M];
  this->removed = new bool[M];

  for (int i = 0; i < this->M; i++) {
    this->empty[i] = true;
    this->removed[i] = false;
  }
};

itemType Hash_EA::search(string key, string type) {
  itemType aux;  // construtor seta o item para -1;
  int pos, i;
  pos = Hash(key, type);
  i = 0;
  while ((i < M) && !empty[(pos + i) % M] &&
         (Table[(pos + i) % M].verbete != key || Table[(pos + i) % M].type != type))
    i++;
  if ((Table[(pos + i) % M].verbete == key) && !removed[(pos + i) % M]) {
    aux = Table[(pos + i) % M];
  }
  return aux;
}

void Hash_EA::insert(itemType item) {
  int pos, i;

  pos = Hash(item.verbete, item.type);
  i = 0;
  while ((i < M) && !empty[(pos + i) % M] && !removed[(pos + i) % M]) {
    if(Table[(pos + i) % M].verbete==item.verbete && Table[(pos + i) % M].type==item.type) {
      for(int j = 0; j < item.n; j++) {
       Table[(pos + i) % M].setMean(item.significados[j]);
      }
      return;
    }
    i++;
  }
  if (i == M)
    throw("Erro: Tabela está cheia");
  else {
    Table[(pos + i) % M] = item;
    empty[(pos + i) % M] = false;
    removed[(pos + i) % M] = false;
  }
}

void Hash_EA::remove(string key, string type) {
  int pos, i;
  pos = Hash(key, type);
  i = 0;

  while ((i < M) && !empty[(pos + i) % M] &&
         (Table[(pos + i) % M].verbete != key && Table[(pos + i) % M].type != type))
    i++;

  if ((Table[(pos + i) % M].verbete == key && Table[(pos + i) % M].type == type) &&
      !removed[(pos + i) % M])
    removed[(pos + i) % M] = true;
  else
    throw("Erro: Item não está presente");
}

void Hash_EA::remove_all_with_mean() {
  for (int i = 0; i < this->M; i++) {
    if (Table[i].n) {
      removed[i] = true;
    }
  }
}

int Hash_EA::Hash(string key, string type) {
  int sum = 0;
  for (auto k : key) {
    sum += k;
  }
  sum += type[0];
  return sum % M;
}

void Hash_EA::print(std::fstream& out) {
  selection(this->Table, this->empty, this->removed, 0, this->M - 1);
  for (int i = 0; i < this->M; i++) {
    if (!empty[i] && !removed[i])
      Table[i].print(out);
  }
}