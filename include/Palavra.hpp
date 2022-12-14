#ifndef PALAVRA
#define PALAVRA
#include <iostream>
#include <string>
#include <fstream>

// ADT that represents a word mean;
class Significado {
 public:
  // Constructors
  Significado() {}
  Significado(std::string s) {
    this->significado = s;
  }
  // Change the mean
  void setSignificado(std::string s) {
    this->significado = s;
  }
  // Containg the mean
  std::string significado;
};

class Verbete {
 public:
  // Constructors
  Verbete() {
    n = 0;
    verbete = "";
  }
  Verbete(std::string v, std::string type) {
    n = 0;
    this->verbete = v;
    this->type = type;
  }
  // Reset
  void clear() {
    this->verbete = "";
    n = 0;
  }
  // Add a new mean
  void setMean(std::string s) {
    if(s.size()){
      this->significados[n] = s;
      n++;
    }
  }
  void setType(std::string s) {
    this->type = s;
  }
  // Change the word
  void setVerbete(std::string v) {
    this->verbete = v;
  }
  // Print the word and its means
  void print(std::fstream& out) {
    out << this->verbete << " (" + type + ")\n";
    for (int i = 0; i < n; i++) {
      out << i + 1 << ". " + significados[i] << '\n';
    }
  }
  // Contains the word
  std::string verbete;
  // Contains the means
  std::string significados[20];
  // Number of means
  int n;
  // Word type
  std::string type;
};

#endif