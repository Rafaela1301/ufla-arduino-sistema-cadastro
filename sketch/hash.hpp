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
int funcaoHash(int chave, int qtdBin) { //Função que calcula o Hash
  int h = 0;
  int numeroBit = pow(2, (qtdBin));
  h = chave % numeroBit;
  return h;
}
class TabelaHash { //Class TabelaHash
  private:
    int altura;
  public:
    TabelaHash(unsigned cap) { // construtor
      // construtor
      File alt = SD.open("alt.txt");
      if (alt) {
        int *alturaTrie = new int;
        alt.read((char *)alturaTrie, sizeof(int));
        altura = *alturaTrie;
      }
      else {
        altura = 3;
        alt.close();
      }
    }

    void insere(int id, int matricula) {
    }
    void insereAux(int id, int matricula) {
      int h;
      h = funcaoHash(id, altura);
      int *vet = new int[altura];
      vet = intToBin(h);
      int posInsercao = 0;

      for (int i = 0; i < altura; i++)
      {
        if (vet[i] == 0)
        {
          posInsercao += esquerda(posInsercao);
        }

        else
        {
          posInsercao += direita(posInsercao);
        }
      }
      int *posicaoArquivo = new int;
      *posicaoArquivo = posInsercao * sizeof(Bloco);
      Bloco *blocoHash = new Bloco;
      bool verificador = verificaChaveAux(*posicaoArquivo);
      if (verificador)
      {
        File userAux = SD.open("infoAux.txt");
        userAux.seek(*posicaoArquivo/*, userAux.beg*/);
        userAux.read((char *)blocoHash, sizeof(Bloco));
        userAux.close();
      }
      if (blocoHash->bTamanho < 4)
      {
        if (!verificaId(blocoHash, id))
        {
          blocoHash->vetor[blocoHash->bTamanho].mId = id;
          blocoHash->vetor[blocoHash->bTamanho].mMatricula = matricula;

          blocoHash->bTamanho++;

          File userAux = SD.open("infoAux.txt");
          if (userAux) {
            userAux.close();
            File userAux =  SD.open("infoAux.txt", FILE_WRITE);
            userAux.seek(*posicaoArquivo);
            userAux.write((char *)blocoHash, sizeof(Bloco));
            userAux.close();
          }
          else
          {
            userAux.close();
            File plantaAux = SD.open("infoAux.txt");
            userAux.seek(*posicaoArquivo);
            userAux.write((char *)blocoHash, sizeof(Bloco));
            userAux.close();
          }

          if ((blocoHash->bTamanho - 1) == 0)
          {
            File mapaAux = SD.open("mapeamentoAux.txt", FILE_WRITE);
            mapaAux.write((char *)posicaoArquivo, sizeof(int));
          }
        }

        else {
          Serial << "\nID já inserido";
        }
      } else {
        redimensiona();
      }
    }
    void percorre() {

      File user = SD.open("cerrado.txt");
      if (user) {
        File mapa = SD.open("mapeamento.txt");
        if (mapa) {
          int *ph = new int;
          Bloco *atual = new Bloco;
          int outrocontador = 0;
          mapa.seek(0);
          int tam = mapa.position();
          mapa.seek(0);
          for (unsigned int i = 0; i < tam / sizeof(int); i++) {
            mapa.read((char *)ph, sizeof(int));
            if (*ph != -1)
              outrocontador++;
          }
          mapa.close();
          File mapa2 = SD.open("mapeamento.txt");
          for (int j = 0; j < outrocontador; j++) {
            mapa2.read((char *)ph, sizeof(int));
            if (*ph == -1)
              j--;
            else {
              user.seek(*ph);
              user.read((char *)atual, sizeof(Bloco));
              int maisumcontador = 0;
              int posValida;
              while (maisumcontador < 4)
              {
                if (atual->vetor[maisumcontador].mId != -1)
                {
                  posValida = maisumcontador;
                }
                maisumcontador++;
              }
              Serial << "\nBloco: " << funcaoHash(atual->vetor[posValida].mId, altura);
              for (int i = 0; i < 4; i++)
              {
                if (atual->vetor[i].mId != -1)
                {

                  Serial << "Id: " << atual->vetor[i].mId;

                  Serial << "Matricula: " << atual->vetor[i].mMatricula;
                }
              }
            }
          }
          user.close();
          mapa2.close();
        } else
          Serial << "Arquivo Vazio";
      } else {
        Serial << "Arquivo Vazio";
      }
    }
    void imprimirOrdenado(int bloco);
    void remover(int id) {
      int h;
      h = funcaoHash(id, altura);
      int *vet = new int[altura];
      vet = intToBin(h);
      int posRemocao = 0;

      for (int i = 0; i < altura; i++)
      {
        if (vet[i] == 0)
        {
          posRemocao += esquerda(posRemocao);
        }

        else
        {
          posRemocao += direita(posRemocao);
        }
      }
      int *posicaoArquivo = new int;
      *posicaoArquivo = posRemocao * sizeof(Bloco);
      File mapa = SD.open("mapeamento.txt");
      bool sinalizador = false;
      int *posEmBytes = new int;
      File user = SD.open("info.txt");
      Bloco *blocoHash = new Bloco;
      user.seek(*posicaoArquivo);
      user.read((char *)blocoHash, sizeof(Bloco));
      char null[1];
      null[0] = '%';
      if (blocoHash->vetor[0].mId == id || blocoHash->vetor[1].mId == id || blocoHash->vetor[2].mId == id || blocoHash->vetor[3].mId == id) {
        for (int i = 0; i < 4; i++) {
          if (blocoHash->vetor[i].mId == id) {
            blocoHash->vetor[i].mId = -1;
            blocoHash->vetor[i].mMatricula = -1;
          }
        }
        blocoHash->bTamanho--;
        user.seek(*posicaoArquivo);
        user.write((char *)blocoHash, sizeof(Bloco));
        int outrocontador = 0;
        if (blocoHash->bTamanho == 0) {
          int *inatividade = new int;
          *inatividade = -1;
          while (!mapa.available() and !sinalizador)
          {
            outrocontador++;
            mapa.read((char *)posEmBytes, sizeof(int));
            if (*posicaoArquivo == *posEmBytes) {
              mapa.seek((outrocontador - 1) * sizeof(int));
              mapa.write((char *)inatividade, sizeof(int));
              sinalizador = true;
            }

          }
        }
      } else {
        Serial << "ID NÃO ENCONTRADO";
      }
      mapa.close();
      user.close();
    }
    bool verificaChave(int h) {
      File entradaMapa =  SD.open("mapeamento.txt");
      int *ph;
      ph = new int;
      bool indicador = false;
      if (entradaMapa)
      {
        while (!entradaMapa.available() && indicador == false)
        {
          entradaMapa.read((char *)ph, sizeof(int));
          if (h == *ph)
          {
            indicador = true;
          }
        }
      }
      entradaMapa.close();
      return indicador;
    }
    bool verificaChaveAux(int h);
    bool verificaId(Bloco* blocoHash, int id);
    int* intToBin(int c) {
      int *binVet = new int[altura];
      for (int i = altura - 1; i >= 0; i--) {
        binVet[i] = c % 2;
        c /= 2;
      }
      return binVet;
    }
    Bloco* busca(int c) {
      int h;
      h = funcaoHash(c, altura);
      int *vet = new int[altura];
      vet = intToBin(h);
      int posInsercao = 0;
      for (int i = 0; i < altura; i++) {
        if (vet[i] == 0) {
          posInsercao += esquerda(posInsercao);
        } else {
          posInsercao += direita(posInsercao);
        }
      }
      int posicaoArquivo;
      posicaoArquivo = posInsercao * sizeof(Bloco);
      Bloco *blocoHash = new Bloco;
      File user = SD.open("info.txt");
      user.seek(posicaoArquivo /*, user.beg*/);
      user.read((char *)blocoHash, sizeof(Bloco));
      for (int i = 0; i < 4; i++) {
        if (blocoHash->vetor[i].mId == c) {
          return blocoHash;
        }
      }
      return NULL;
    }
    void imprimeBuscado(int c) {
      Bloco* buscado = new Bloco;
      buscado = busca(c);
      if (buscado == NULL) {
        Serial << "ID não encontrado!";
      } else {
        for (int cont = 0; cont < 4; cont++) {
          if (buscado->vetor[cont].mId != -1) {
            if (buscado->vetor[cont].mId == c) {
              Serial << "Id: " <<  buscado->vetor[cont].mId ;
              Serial << "Matricula: " <<  buscado->vetor[cont].mMatricula;
            }
          }
        }
      }
    }
    int esquerda(int posicao) {
      posicao = (posicao * 2) + 1;
      return posicao;
    }
    int direita(int posicao) {
      posicao = (posicao * 2) + 2;
      return posicao;
    }
    void redimensiona() {
      File user = SD.open("cerrado.txt");
      File mapa = SD.open("mapeamento.txt");
      mapa.seek(0/*, mapa.end*/);
      int tam = mapa.position();
      mapa.seek(0/*, mapa.beg*/);
      altura++;
      int *posEmBytes = new int;
      Bloco *blocoHash = new Bloco;
      for (unsigned int i = 0; i < (tam / sizeof(int)); i++)
      {
        mapa.read((char *)posEmBytes, sizeof(int));
        user.seek(*posEmBytes);
        user.read((char *)blocoHash, sizeof(Bloco));
        for (int j = 0; j < 4; j++)
        {
          if (blocoHash->vetor[j].mId != -1)
          {

            insereAux(blocoHash->vetor[j].mId, blocoHash->vetor[j].mMatricula);
          }
        }
      }
      File modAltura =  SD.open("alt.txt", FILE_WRITE);
      int *altWrite = new int;
      *altWrite = altura;
      modAltura.write((char *)altWrite, sizeof(char));
      SD.remove("info.txt");
      SD.remove("mapeamento.txt");
      rename("infoAux.txt", "info.txt");
      rename("mapeamentoAux.txt", "mapeamento.txt");
      user.close();
      mapa.close();
    }


};
#endif
