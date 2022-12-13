#ifndef HASH_EA
#define HASH_EA

#include "Palavra.hpp"
using namespace std;
#define keyType string
#define itemType Verbete

class Hash_EA {
 public:
 //Constructors
  Hash_EA(int len);
  ~Hash_EA();
 //Insert a new item
  void insert(itemType item);
  //Remove the item with the specifications
  void remove(keyType key, string type);
  //Search for the item
  itemType search(keyType key, string type);

 private:
  //Contains the length of Table
  int M;
  //Represents the table
  itemType *Table;
  //Indicates if the position is empty or removed
  bool *empty;
  bool *removed;
  //Function to calculate the position on table
  int Hash(keyType key);
};
#endif