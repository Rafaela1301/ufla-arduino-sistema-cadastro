#include "no.hpp"
#include "bloco.hpp"
#include "hash.hpp"
#include <SPI.h>
#include <SD.h>
#include <SPI.h>

//#include <MFRC522.h>
/*
  #define SS_PIN 10
  #define RST_PIN 9

  MFRC522 mfrc522(SS_PIN, RST_PIN);*/
TabelaHash objeto(16);
void setup() {
  Serial.begin(9600); // Inicializa a comunicação serial com uma taxa de 9600 bauds.
  Serial.print("Inicializa SD card...");
  if (!SD.begin(4)) {
    Serial.println("inicializacao falhou!");
    while (1);
  }
  Serial.println("Inicializado!.");
  objeto.percorre();
}

void loop() {

  int id = 0; // deveria ser o codigo do cartão rfid mas não conseguimos utilizar ele junto com o cartão SD
  int matricula = 0;
  int busca = 0;
  
  if (Serial.available() > 0) {
    Serial << "Informe id para nova insercao:";
    id = Serial.parseInt();

  }
  if (Serial.available() > 0) {
    Serial<<"Informe matricula para nova insercao: ";
    matricula = Serial.parseInt();


  }
  if (matricula != 0 and id != 0) {
    objeto.insere(id, matricula);
    Serial << "Inserido com sucesso!";
  }
  if (Serial.available() > 0) {
    Serial <<"Informe id para buscar:";
      busca = Serial.parseInt();
    }
    if (busca != 0) {
      objeto.consulta(busca);
    }


}
