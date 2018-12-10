#ifndef LISTA_H
#define LISTA_H

#include "Noh.hpp" //Importando arquivo que contém class No
#include <SD.h>

template <typename T>

inline Print& operator << (Print& streamer, const T& x) { // sobrecarga do operador <<
  streamer.println(x);
  return streamer;
}

class noh {
    friend class Lista;
  private:
    short int dado;
    int chave;
    noh* proximo = NULL;
  public:
    noh() {
      dado = 0;
      chave = 0;
    }
};

class Lista {

  private:
    noh* primeiro;
    noh* ultimo;
    int tamanho;
  public:
    Lista() {
      tamanho = 0;
      primeiro = NULL;
      ultimo = NULL;
    }
    ~Lista() {
      noh* iter = primeiro;
      noh* proximo = NULL;
      while (iter != NULL) {
        proximo = iter->proximo;
        delete iter;
        iter = proximo;
      }
    }
    void insere(short int dado, int chave) { // insere de maneira ordenada
      noh* aux = new noh;
      aux->dado = dado;
      aux->chave = chave;
      if (vazia()) {
        primeiro = aux;
        ultimo = aux;
      } else if (aux->dado < primeiro->dado) {
        aux->proximo = primeiro;
        primeiro = aux;
      } else if (aux->dado > ultimo->dado) {
        ultimo->proximo = aux;
        ultimo = aux;
      } else {
        noh* anterior;
        noh* atual = primeiro;
        bool valida = false;
        while (atual != NULL and valida == false) { // procura o maior que o dado inserido
          if (aux->dado <= atual->dado ) {
            aux->proximo = atual;
            anterior->proximo = aux;
            valida = true;
          }
          anterior = atual;
          atual =  atual->proximo;

        }
      }
      tamanho++;
    }

    void imprimeNoArquivo() {

      File lumens = SD.open("lumens.txt", O_CREAT | O_WRITE | O_APPEND); //O_CREAT | O_WRITE | O_APPEND cria o arquivo se nao existir

      noh* aux = primeiro;
      if (lumens) {
        while (aux != NULL) {
          lumens.print(aux->dado);
          lumens.print("/");
          lumens.println(aux->chave);
          aux = aux->proximo;
        }
        Serial << "";
      } else {
        Serial << "Erro ao abrir arquivo";
      }
      lumens.close();
    }
    void exibeDadosArquivo() {
      File lumens = SD.open("lumens.txt");// O_CREAT | O_WRITE | O_APPEND cria o arquivo se nao existir
      Serial << "LENDO DADOS DO ARQUIVO";
      if (lumens) {
        while (lumens.available()) {
          Serial.write(lumens.read());
        }

      } else {
        Serial << "Erro ao abrir arquivo";
      }
      lumens.close();
    }

    void remover (int posicao) {
       SD.remove("lumens.txt");

      if (posicao >= 0  and posicao < tamanho and !vazia()) {
        if (posicao == 0) {
          noh* aux = primeiro;
          primeiro = primeiro->proximo;
          delete aux;
        } else {
          noh* atual = primeiro->proximo;
          noh* ant = primeiro;
          int posAux = 1;
          while (posAux < posicao) {
            ant = atual;
            atual = atual->proximo;
            posAux++;
          }
          if (atual == ultimo) {
            ant->proximo = NULL;
            ultimo = ant;
            delete atual;
          } else {
            ant->proximo = atual->proximo;
            delete atual;
          }

        }
        tamanho--;
      }
    }
    void imprime() {
      noh* aux = primeiro;
      while (aux != NULL) {
        Serial << aux->dado << " ";
        aux = aux->proximo;
      }
      Serial << "";
    }
    inline bool vazia() {
      return (primeiro == NULL);
    }
};
#endif
