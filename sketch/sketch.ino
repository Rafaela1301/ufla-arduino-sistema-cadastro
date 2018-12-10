/*******************************************************************************

     Projeto 30 – Sensor de luz LDR com sinalizador de Leds
                    http://squids.com.br/arduino

*******************************************************************************/
#include <SPI.h>
#include <SD.h>
#include "TabelaHash.hpp"
#include "Noh.hpp"
#include "Lista.hpp"

const int buzzerPin = 7; // Piezo no pino 8
const int ldrPin = 0; // LDR no pino analógico 0
const int ledPin = 3; // LED no pino digital 3

const int ledVerde = 8;
const int ledAmarelo = 9;
const int ledVermelho = 10;

short int qtd_itens = 40;
int ldrValue = 0; // Valor lido do LDR
const int freq = 5; // altera frequencia do sonorizador
TabelaHash tabela(40);
Lista lista;

void setup() {
  SD.remove("lumens.txt");
  //Ativando o serial monitor que exibirá os valores lidos no sensor.
  Serial.begin(9600);
  //Definindo pinos digitais dos leds e buzzer como de saída.
  pinMode(ledPin, OUTPUT);
  pinMode(ledVerde, OUTPUT);
  pinMode(ledAmarelo, OUTPUT);
  pinMode(ledVermelho, OUTPUT);
  randomSeed(analogRead(0));

  Serial.begin(9600);
  while (!Serial) {
    ; // wait for serial port to connect. Needed for native USB port only
  }


  Serial.print("Initializing SD card...");

  if (!SD.begin(4)) {
    Serial.println("initialization failed!");
    while (1);
  }
  Serial.println("initialization done.");
  int id;


  for (int i = 0; i < qtd_itens; i++) {
    ldrValue = analogRead(ldrPin); // lê o valor do LDR
 
    lista.insere(ldrValue, i);
    //tabela.insere(ldrValue, i);
    
    //Luminosidade baixa.
    if (ldrValue < 300) {
      apagaLeds();
      digitalWrite(ledVermelho, HIGH);

      //toca o alarme
      digitalWrite(ledPin, HIGH);
      delay(25); // espera um pouco
      digitalWrite(ledPin, LOW);
      delay(ldrValue); // espera a quantidade de milissegundos em ldrValue
    }

    //Luminosidade média.
    if (ldrValue >= 300 && ldrValue <= 500) {
      apagaLeds();
      digitalWrite(ledAmarelo, HIGH);
    }

    //Luminosidade alta.
    if (ldrValue > 500) {
      apagaLeds();
      digitalWrite(ledVerde, HIGH);
    }

    //Exibindo o valor do sensor no serial monitor.
    Serial.println(ldrValue);
    delay(200);
  }

  lista.imprimeNoArquivo();
  lista.exibeDadosArquivo();
  int randon = random(0, 39); // variavel que gera um numero aleatorio para buscar (nao conseguimos a busca pelo teclado);

  Serial.print("Buscar a posicao: ");
  Serial.print(randon);
  Serial << "...";
  tabela.recupera(randon);

  randon = random(0, 39);
  Serial.print("Remover a posicao: ");
  Serial.print(randon);
  Serial << "...";

  lista.remover(randon);
  Serial << "DADOS APOS REMOCAO";

  lista.imprimeNoArquivo();
  lista.exibeDadosArquivo();

 
}

void loop() {

}

//Função criada para apagar todos os leds de uma vez.
void apagaLeds() {
  digitalWrite(ledVerde, LOW);
  digitalWrite(ledAmarelo, LOW);
  digitalWrite(ledVermelho, LOW);
}
