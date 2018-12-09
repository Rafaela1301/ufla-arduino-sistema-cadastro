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
#ifndef NO_H
#define NO_H
class No { //class No
    friend class TabelaHash; //class No amiga da  class TabelaHash
    friend class Bloco;

public:
    //Construtor
    No() {
        mId = -1;
        mMatricula = -1;
    }
private:
    //Atributos
    int mId;
    int mMatricula;

};
#endif 
