#ifndef NO_H
#define NO_H

#include "TabelaHash.hpp"
#include "Lista.hpp"

class Noh {
    friend class TabelaHash;
    friend class Lista;
  private:
    short int dado;
    int chave;
    Noh* proximo = NULL;
  public:
    Noh() {
      dado = 0;
      chave = 0;
    }
};
#endif
