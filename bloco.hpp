/* 
  Trabalho de Estruturas de Dados
  Sistema de Cadastro     
  Copyright 2018 by Rafaela Custódio, Marcelo Henrique, Thiago Fiori
  
  Funcionalidades dos arqquivos:
 * Arquivo Main.cpp - Possui a função principal 
 * No.hpp - Arquivo contendo a classe No
 * Bloco.hpp - Arquivo contendo a classe Bloco
 * TabelaHash.hpp - Arquivo que contem a class TabelaHash
 * info.txt - arquivo binário onde os dados são salvos
 * mapa.txt - arquivo binario de mapeamento do arquivo info
 */
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
