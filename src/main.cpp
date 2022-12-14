#include <assert.h>
#include <iostream>
#include <sstream>
#include <fstream>

#include "AVLTree.hpp"
#include "Hash_EA.hpp"
#include "Dictionary.hpp"
#include "Palavra.hpp"
using namespace std;

int main(int argc, char *argv[]) {
  // Declaring all variables
  string input, output, dictType;
  fstream dataIn, dataOut;
  int inputLen;
  // Reading argv
  for (int i = 1; i < argc; i += 2) {
    if ((string)argv[i] == "-i") {
      input = argv[i + 1];
    } else if ((string)argv[i] == "-o") {
      output = argv[i + 1];
    } else if ((string)argv[i] == "-t") {
      dictType = argv[i + 1];
    }
  }
  // Assertions
  assert(input.size()>0);
  assert(output.size()>0);
  assert(dictType == "hash" || dictType == "arv");

  // Open archives
  dataIn.open(input, fstream::in);
  dataOut.open(output, fstream::out);

  // Getting number of lines in input
  // dataIn.seekg (0, dataIn.end);
  // inputLen = dataIn.tellg();
  // dataIn.seekg (0, dataIn.beg);
  inputLen = 5000;
  // Crating the dictionary
  Dictionary *dict;
  if(dictType == "hash")
   dict =  new Hash_EA{inputLen};
  else dict = new AVL_Tree;

  //Inserting the words
  string type, verb, mean, line;
  int colchete;
  while(getline(dataIn, line)) {
    Verbete v;
    mean = "";
    type = line[0];
    colchete = line.find("]");
    verb = line.substr(3,colchete-3);
    if(colchete+1 < line.size())
      mean = line.substr(colchete+2,line.size());
    v.setVerbete(verb);
    v.setMean(mean);
    v.setType(type);

    dict->insert(v);
  }
  dict->print(dataOut);
  dict->remove_all_with_mean();
  dict->print(dataOut); 
  return 0;
}