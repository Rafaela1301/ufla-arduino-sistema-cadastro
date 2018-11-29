#ifndef TABELA_HASH_H
#define TABELA_HASH_H
#include "no.hpp" //Importando arquivo que contém class No
#include "bloco.hpp"
#include <SD.h>
class TabelaHash { //Class TabelaHash
  public:
    TabelaHash() { // construtor
      File alt = SD.open("alt.txt");
      if (alt)
      {
        int *alturaTrie = new int;
        alt.read((char *)alturaTrie, sizeof(int));
        altura = *alturaTrie;
      }
      else
        altura = 3;

      alt.close();
    }
    void insere(int matricula, int id);
    void insereAux(int matricula, int id);
    void percorre();
    void imprimirOrdenado(int bloco);
    void remover(int _id);
    bool verificaChave(int h);
    bool verificaChaveAux(int h);
    bool verificaId(Bloco* blocoHash, int id);
    int* intToBin(int c);
    Bloco* busca(int c);
    void imprimeBuscado(int c);
    int esquerda(int posicao);
    int direita(int posicao);
    void redimensiona();
  private:
    //Atributos
    int altura;
};
#endif
