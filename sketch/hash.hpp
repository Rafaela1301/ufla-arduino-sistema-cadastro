#ifndef TABELA_HASH_H
#define TABELA_HASH_H
#include "no.hpp" //Importando arquivo que contém class No
#include "bloco.hpp"
#include "lista.hpp"
#include <SD.h>

class TabelaHash { //Class TabelaHash
  public:
    TabelaHash(unsigned cap) { // construtor
      mCapacidade = cap;
    }
    //Função que calcula o Hash
    int funcaoHash(int chave, int capacidade) {
      int h = 0;
      h = chave % (capacidade);
      return h;
    }

    void insere(int matricula, int id) { // insere no arquivo
      File saidaMapa = SD.open("mapa.txt", FILE_WRITE);
      File saida = SD.open("info.txt", FILE_WRITE);
      int h = funcaoHash(id, mCapacidade);
      int copiaH = h;
      bool indicador = verificaChave(h); //verifica a chave no arquivo mapa.txt e retorna um indicador
      int *ph;
      ph = new int;
      ph = &h;
      if (indicador == 0) {
        if (!verificaInativa()) {
          Bloco blocoHash;
          No novo;
          novo.mId = id;
          novo.mMatricula = matricula;
          blocoHash.bLista.insere(novo);
          blocoHash.bTamanho++;
         
          // se arquivo estiver ok escreve:
         /* if (saida) {
            Serial.print("Salvando...");
            saida.println(blocoHash);
            // close the file:
            saida.close();
            Serial.println("Salvo.");
          } else {
            // if the file didn't open, print an error:
            Serial.println("error opening info.txt");
          }*/
         if (saidaMapa) {
            Serial.print("Salvando...");
            saidaMapa.println(ph);
            // close the file:
            saidaMapa.close();
            Serial.println("Salvo.");
          } else {
            // if the file didn't open, print an error:
            Serial.println("error opening info.txt");
          }
        } else {

        }
      } else {

      }

    }
    void percorre();
    void imprimirOrdenado(int bloco);
    void remover(int id);

    bool verificaChave(int h) { // verifica se a chave existe

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
        entradaMapa.close();
      } else {
        Serial.println("error opening mapa.txt");
      }
      return indicador;
    }
    int achaPosicao(int h);
    bool verificaId(Bloco* blocoHash, int id);

    bool verificaInativa() { //verifica posicao inativa
      bool indicadorInativo = 0;
      int *ph;
      ph = new int;
      File entradaMapa = SD.open("mapa.txt");
      if (entradaMapa) {
        while (*ph != -1 && !entradaMapa.available()) {
          *ph = entradaMapa.read();
          if (*ph == -1) {
            indicadorInativo = 1;
          }
        }
      }
      delete ph;
      entradaMapa.close();
      return indicadorInativo;
    }
    int posInativa(int h);
    void consulta(int id);
  private:
    //Atributos
    int mCapacidade;
};
#endif
