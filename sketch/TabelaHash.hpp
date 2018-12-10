#ifndef TABELA_HASH_H
#define TABELA_HASH_H
#include "Noh.hpp" //Importando arquivo que contém class No
#include <SD.h>
int funcaoHash(int chave, int capacidade) {
  int h = 0;
  h = chave % capacidade;
  return h;
}

class TabelaHash {
  private:
    Noh** elementos;
    int capacidade;
  public:
    TabelaHash(int cap = 40) {
      elementos = new Noh*[cap];
      capacidade = cap;
      for (int i = 0; i < capacidade; i++) {
        elementos[i] = NULL;
      }
    }
    ~TabelaHash() {
      for (int i = 0; i < capacidade; i++) {
        Noh* atual = elementos[i];

        while (atual != NULL) {
          Noh* aux = atual;
          atual = atual->proximo;
          delete aux;
        }
      }
      delete[] elementos;
    }
    void insere(short int d, int chave) {
      int h = funcaoHash(chave, capacidade);
      if (elementos[h] == NULL) {
        elementos[h] = new Noh;
        elementos[h]->dado = d;
        elementos[h]->chave = chave;
      } else {
        while (elementos[h] != NULL) {
          h++;
          if (h == capacidade) {
            h = 0;
          }
          elementos[h] = new Noh;
          elementos[h]->dado = d;
          elementos[h]->chave = chave;
        }
      }
    }

    int recupera(int hr) {

      int h = funcaoHash(hr, capacidade);
      while (elementos[h] != NULL) {
        if ((elementos[h] != NULL) and (elementos[h]->chave == hr)) {
          Serial << "Chave: " << elementos[h]->chave;
          Serial << "Luminosidade: " << elementos[h]->dado;
          return h;
        } else {
          h++;
        }
      }
      return h;
    }
    
    void percorre( ) {
      Noh* atual;
      for (int i = 0; i < capacidade; i++) {
        Serial << i << ":";
        atual = elementos[i];
        while (atual != NULL) {
          Serial.print("[");
          Serial.print(atual->chave);
          Serial.print("/");
          Serial.print(atual->dado);
          Serial.print("]->");
          atual = atual->proximo;
        }
        Serial << "NULL  ";
      }
    }


};
#endif
