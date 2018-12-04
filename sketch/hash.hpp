#ifndef TABELA_HASH_H
#define TABELA_HASH_H
#include "no.hpp" //Importando arquivo que contém class No
#include "bloco.hpp"
#include <SD.h>

class TabelaHash { //Class TabelaHash
  public:
    TabelaHash(unsigned cap) { // construtor
      mCapacidade = cap;
    }
    //Função que calcula o Hash
    int funcaoHash(int chave, int capacidade) {
      long h = 0;
      h = chave % (capacidade);
      return h;
    }

    void insere(int matricula, int id) { // insere no arquivo
      int h = funcaoHash(id, mCapacidade);
      int copiaH = h;
      bool indicador = verificaChave(h);
      Serial.print("sou indicador: ");
      Serial.print(indicador);
      //verifica a chave no arquivo mapa.txt e retorna um indicador

      Serial.print("Inicializa SD card...");
      if (!SD.begin(4)) {
        Serial.println("inicializacao falhou!");
        while (1);
      }
      Serial.println("Inicializado!.");

    }
    void percorre();
    void imprimirOrdenado(int bloco);
    void remover(int _id);
    
    bool verificaChave(int h) {
      File entradaMapa = SD.open("mapa.txt");
      int ph;
      bool indicador = 0;
      if (entradaMapa) {
        while (!entradaMapa.available() && indicador == 0) {
          ph = entradaMapa.read();
          if (h == ph) {
            indicador = 1;
          }
        }
      }else {
        Serial.println("error opening mapa.txt");
      }
      return indicador;
    }
    int achaPosicao(int h);
    bool verificaId(Bloco* blocoHash, int id);
    bool verificaInativa();
    int posInativa(int h);
    void consulta(int id);
  private:
    //Atributos
    int mCapacidade;
};
#endif
