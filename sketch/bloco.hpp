
#ifndef BLOCO_H
#define BLOCO_H
#include "no.hpp"
#include "lista.hpp"
#include "dado.hpp"

class Bloco { //class No
    friend class TabelaHash; //class No amiga da  class TabelaHash
    friend class No;
public:
    //Construtor

    Bloco() {
        bTamanho = 0;
        bAtivo = true;
        
    }
    
private:
    //Atributos
    int bTamanho;
    bool bAtivo;
    Lista bLista;
};
#endif
