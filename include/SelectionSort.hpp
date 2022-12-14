#include "Palavra.hpp"

void selection(Verbete v[], bool empty[], bool removed[], int begin, int end) {
  Verbete aux;
  bool auxE, auxR;
  for (int i = end; i > begin; i--) {
    int biggest = 0;
    for (int j = begin; j <= i; j++) {
      if (v[j].verbete > v[biggest].verbete ||
          (v[j].verbete == v[biggest].verbete &&
           v[j].type > v[biggest].type)) biggest = j;
    }
    aux = v[i];
    auxE = empty[i];
    auxR = removed[i];
    v[i] = v[biggest];
    empty[i] = empty[biggest];
    removed[i] = removed[biggest];
    v[biggest] = aux;
    empty[biggest] = auxE;
    removed[biggest] = auxR;
  }
}