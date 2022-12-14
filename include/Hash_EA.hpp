#ifndef HASH_EA
#define HASH_EA

#include "Palavra.hpp"
#include "Dictionary.hpp"
using namespace std;
#define itemType Verbete

class Hash_EA : public Dictionary {
 public:
 //Constructors
  Hash_EA(){};
  Hash_EA(int len);

 //Insert a new item
  void insert(itemType item);
  //Remove the item with the specifications
  void remove(string key, string type);
  //Search for the item
  itemType search(string key, string type);
  //Print in sequence
  void print(std::fstream& out);
  //Removes all words that contains a mean
  void remove_all_with_mean();
 private:
  //Represents the table
  itemType *Table;
  //Indicates if the position is empty or removed
  bool *empty;
  bool *removed;
  //Function to calculate the position on table
  int Hash(string key, string type);

};
#endif