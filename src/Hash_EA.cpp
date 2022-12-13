#include "Hash_EA.hpp"

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

Hash_EA::~Hash_EA() {
  delete Table;
  delete empty;
  delete removed;
}

itemType Hash_EA::search(keyType key, string type) {
  itemType aux;  // construtor seta o item para -1;
  int pos, i;
  pos = Hash(key);
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
  itemType aux;  // construtor seta o item para -1;
  int pos, i;
  aux = search(item.verbete, item.type);
  if (aux.verbete == "")
    throw("Erro: Item já está presente");

  pos = Hash(item.verbete);
  i = 0;
  while ((i < M) && !empty[(pos + i) % M] && !removed[(pos + i) % M])
    i++;
  if (i == M)
    throw("Erro: Tabela está cheia");
  else {
    Table[(pos + i) % M] = item;
    empty[(pos + i) % M] = false;
    removed[(pos + i) % M] = false;
  }
}

void Hash_EA::remove(keyType key, string type) {
  int pos, i;
  pos = Hash(key);
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

int Hash_EA::Hash(keyType key) {
  int sum = 0;
  for (auto k : key)
    sum += k;
  return sum%M;
}