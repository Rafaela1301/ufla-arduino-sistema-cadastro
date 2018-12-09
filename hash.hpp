/*
  Trabalho de Estruturas de Dados
  Sistema de Cadastro
  Copyright 2018 by Rafaela Custódio, Marcelo Henrique, Thiago Fiori

  Funcionalidades dos arqquivos:
   Arquivo Main.cpp - Possui a função principal
   No.hpp - Arquivo contendo a classe No
   Bloco.hpp - Arquivo contendo a classe Bloco
   TabelaHash.hpp - Arquivo que contem a class TabelaHash
   info.txt - arquivo binário onde os dados são salvos
   mapa.txt - arquivo binario de mapeamento do arquivo info
*/
#ifndef TABELA_HASH_H
#define TABELA_HASH_H
#include "no.hpp" //Importando arquivo que contém class No
#include "bloco.hpp"
#include <SD.h>
template <typename T>

inline Print& operator << (Print& streamer, const T& x) { // sobrecarga do operador <<
  streamer.println(x);
  return streamer;
}
int funcaoHash(int chave, int capacidade) { //Função que calcula o Hash
  int h = 0;
  h = chave % (capacidade);
  return h;
}
class TabelaHash { //Class TabelaHash
  private:
    int mCapacidade;
  public:
    TabelaHash(int cap = 100) {
      mCapacidade = cap;
    }
    void insere(int id, int matricula) {
      File saidaMapa = SD.open("mapa.txt", FILE_WRITE);
      File saida = SD.open("info.txt", FILE_WRITE);
      int h;
      int copiaH = h;

      h = funcaoHash(id, mCapacidade);
      bool indicador = verificaChave(h);
      int *ph;
      ph = new int;
      ph = &h;

      if (indicador == 0) {
        if (!verificaInativa()) {
          Serial << " posicao ativa";
          Bloco* blocoHash = new Bloco;
          blocoHash->vetor[blocoHash->bTamanho].mId = id;
          blocoHash->vetor[blocoHash->bTamanho].mMatricula = matricula;
          blocoHash->bTamanho++;
          saida.write((char *)blocoHash, sizeof (Bloco));
          saidaMapa.write((char *) ph, sizeof (int));
          delete blocoHash;
          saida.close();
          saidaMapa.close();
          Serial << "if";
        } else {
          Serial << "else posicao inativa";
          int posicaoInativa = posInativa(h);
          saidaMapa.seek((posicaoInativa * sizeof (int)));
          saidaMapa.read((char *) ph, sizeof (int));
          *ph = copiaH;
          saidaMapa.seek(posicaoInativa * sizeof (int));
          saidaMapa.write((char *) ph, sizeof (int));
          saidaMapa.close();
          File saida = SD.open("info.txt"); //cria arquivo
          Bloco* blocoHash = new Bloco;
          saida.seek((posicaoInativa * sizeof (Bloco)));
          saida.read((char *) blocoHash, sizeof (Bloco));

          blocoHash->vetor[blocoHash->bTamanho].mId = id;
          blocoHash->vetor[blocoHash->bTamanho].mMatricula = matricula;
          blocoHash->bTamanho++;
          saida.seek(sizeof (Bloco) * (posicaoInativa));
          saida.write((char *) blocoHash, sizeof (Bloco));
          delete blocoHash;
          saida.close();
          Serial << "ELSE";
        }
      } else {
        int pos = achaPosicao(h);
        Serial << "sou pos: " << pos;
        Bloco* blocoHash = new Bloco;
        File entrada = SD.open("info.txt");
        Serial << "p1 antes" << entrada.position();
        entrada.seek((pos * sizeof (Bloco)));
        Serial << "p1" << entrada.position();
        entrada.read((char *) blocoHash, sizeof (Bloco));

        bool indicadorDeId = verificaId(blocoHash, id);
        entrada.close();
        if (indicadorDeId == 0) {
          blocoHash->vetor[blocoHash->bTamanho].mId = id;
          blocoHash->vetor[blocoHash->bTamanho].mMatricula = matricula;

          if (blocoHash->bTamanho < 4) {
            blocoHash->bTamanho++;
            File info = SD.open("info.txt", FILE_WRITE);
            Serial << "p2 antes " << info.position();
            info.seek(sizeof(Bloco) * (pos));
            Serial << "p2 " << info.position();
            info.write((char *) blocoHash, sizeof(Bloco));
            info.close();
            delete blocoHash;
          } else {
            entrada.close();
            Serial << "Erro: bloco lotado!" ;
          }
        } else {
          Serial << "ID já Existe";
        }

      }
    }

    void percorre() {
      File entrada =  SD.open("info.txt");
      File entradaMapa = SD.open("mapa.txt");
      entrada.seek(0);
      int mTam = entrada.size();
      int t = mTam / sizeof(Bloco);
      int* ph;
      ph = new int;
      Bloco* atual = new Bloco;

      for (int i = 0; i < t; i++) {
        entradaMapa.read((char*) ph, sizeof (int));
        if (*ph > -1) {
          Serial << "\nPosição Hash: " << *ph ;
        }
        entrada.read((char*) atual, sizeof (Bloco));
        int cont = 0;
        while (cont < 4) {
          if (atual->vetor[cont].mId != -1) {
            Serial << "Id: " << atual->vetor[cont].mId;
            Serial << "Matricula: " << atual->vetor[cont].mMatricula ;
          }

          cont++;
        }
      }
      entrada.close();
      entradaMapa.close();
    }
    void imprimirOrdenado(int bloco);
    void remover(int id);
    bool verificaChave(int h) {
      File entradaMapa = SD.open("mapa.txt");
      int *ph;
      ph = new int;
      bool indicador = 0;
      if (entradaMapa) {
        while (entradaMapa.available() && indicador == 0) {
          entradaMapa.read((char*) ph, sizeof (int));
          if (h == *ph) {
            indicador = 1;

          }
        }
      }
      entradaMapa.close();
      return indicador;
    }
    int achaPosicao(int h) {
      int cont = 0;
      int *ph;
      ph = new int;
      *ph = -1;
      File entradaMapa =  SD.open("mapa.txt");
      if (entradaMapa) {
        while (*ph != h ) {
          entradaMapa.read((char *) ph, sizeof (int));
          cont++;
        }
      }
      Serial << "sou acha posicao: " << cont - 1;
      entradaMapa.close();
      return cont - 1;
    }
    bool verificaId(Bloco* blocoHash, int id) {
      Serial << "verifica id: " << blocoHash->vetor[0].mId;
      if (blocoHash->vetor[0].mId == id || blocoHash->vetor[1].mId == id || blocoHash->vetor[2].mId == id || blocoHash->vetor[3].mId == id) {
        Serial << "id existe";
        return 1;
      }
      Serial << "id nao existe pode inserir";
      return 0;
    }
    bool verificaInativa() {
      bool indicadorInativo = 0;
      int *ph;
      ph = new int;
      File entradaMapa = SD.open("mapa.txt");
      if (entradaMapa) {
        while (*ph != -1 && entradaMapa.available()) {
          entradaMapa.read((char *) ph, sizeof (int));
          if (*ph == -1)
            indicadorInativo = 1;
        }
      }
      delete ph;
      entradaMapa.close();
      return indicadorInativo;
    }
    int posInativa(int h) {
      int cont = 0;
      int *ph;
      ph = new int;
      File entradaMapa = SD.open("mapa.txt");
      if (entradaMapa) {
        entradaMapa.read((char *) ph, sizeof (int));
        while (*ph != -1) {
          entradaMapa.read((char *) ph, sizeof (int));
          cont++;
        }
      }
      entradaMapa.close();
      return cont;
    }
    void consulta(int id) {
      int h;
      h = funcaoHash(id, mCapacidade);
      bool indicador = verificaChave(h);
      Serial << "consulta, sua chave: ";
      Serial << h;
      if (indicador) {
        Serial << "indicador";
        int pos = achaPosicao(h);
        Bloco* blocoHash = new Bloco;
        File entrada = SD.open("info.txt");
        entrada.seek((pos * sizeof (Bloco)));
        entrada.read((char *) blocoHash, sizeof (Bloco));
        if ((id == blocoHash->vetor[0].mId) or (id == blocoHash->vetor[1].mId) or (id == blocoHash->vetor[2].mId) or (id == blocoHash->vetor[3].mId)) {
          Serial << "procura a chave no bloco";
          for (int i = 0; i < blocoHash->bTamanho; i++) {
            if (id == blocoHash->vetor[i].mId) {
             Serial << "Id: " << blocoHash->vetor[i].mId ;
             Serial << "Matricula: " << blocoHash->vetor[i].mMatricula;
            }
          }
        }else{
          Serial << "O ID não foi encontrado";
        }
      }else{
        Serial << "O ID não foi encontrado" ;
      }
    }


};
#endif
