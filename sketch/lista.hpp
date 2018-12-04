#ifndef LISTA_H
#define LISTA_H
#include "dado.hpp"
#include "no.hpp"
class Lista {
  private:
    Dado* lPrimeiro;
    Dado* lUltimo;
    int lTamanho;
    int lCapacidade;
  public:
    Lista() {
      lTamanho = 0;
      lCapacidade = 4;
      lPrimeiro = NULL;
      lUltimo = NULL;
    }
    ~Lista() {
      Dado* iter = lPrimeiro;
      Dado* proximo = NULL;
      while (iter != NULL) {
        proximo = iter->dProximo;
        delete iter;
        iter = proximo;
      }
      lTamanho = 0;
    }


    void insere(No dado) {
      // insere por padrão no final da lista
      if (lTamanho < lCapacidade) {
        Dado* aux = new Dado(dado);
        if (vazia()) {
          lPrimeiro = aux;
          lUltimo = aux;
        } else {
          lUltimo->dProximo = aux;
          lUltimo = aux;
        }
        lTamanho++;
      }else{
        Serial.println("Bloco cheio!");
      }
    }

    inline bool vazia() {
      return (lPrimeiro == NULL);
    }
};
#endif
