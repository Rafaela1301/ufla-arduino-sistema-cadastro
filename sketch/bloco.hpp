
#ifndef BLOCO_H
#define BLOCO_H
#include "no.hpp"

class Bloco { //class No
    friend class TabelaHash; //class No amiga da  class TabelaHash
    friend class No;
public:
    //Construtor

    Bloco() {
        bTamanho = 0;
        ativo = true;
        for (int i = 0; i < 4; i++) {
            vetor[i].mId = -1;
        }
    }
    
private:
    //Atributos
    int bTamanho;
    bool ativo;
    No vetor[4];
};
#endif
