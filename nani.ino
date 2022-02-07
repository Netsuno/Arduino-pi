/*
 Capteur Abrastop
 Lit la valeur des capteur et l'envois par le port Serial (USB)
 Version 1.1

 */
#include "math.h"

const int sensorPin0 = A0;  // pin pour le sensor 0
const int sensorPin1 = A1; //pin pour le sensor 1
const int sensorPin2 = A2; //pin pour le sensor 2
const int inPin = 7; //Push button du zero
int sensorValue0 = 0; // int de la valeur du sensor 0
int sensorValue1 = 0; // int de la valeur du sensor 1 (du haut)
int sensorValue2 = 0; // int de la valeur du sensor 2 (du bas)
int sensorValeur0 = 0; // Valeur difference du sensor 0 avec le point zero du debut
int sensorValeur1 = 0; // Valeur difference du sensor 0 avec le point zero du debut
int sensorValeur2 = 0; // Valeur difference du sensor 0 avec le point zero du debut
int sensorZero0 = 0; // Zero du sensor 0
int sensorZero1 = 0; // Zero du sensor 1
int sensorZero2 = 0; // Zero du sensor 2
int sensorTotal; //Result total des calcule
int data [10];
int readIndex = 0;
int total = 0;
float average = 0;



void setup() {
Serial.begin(9600); //Déclaration de la communication sérial
pinMode(inPin, INPUT_PULLUP); //Type de pin 
for (int i = 0; i < 10; i++){
  data[i] = 0;
}
}

void loop() {

 while (digitalRead(inPin) == LOW){
 sensorValue0 = analogRead(sensorPin0);  //Lire la valeur du sensor 0
 sensorValue1 = analogRead(sensorPin1); //Lire la valeur du sensor 1
 sensorValue2 = analogRead(sensorPin2); //Lire la valeur du sensor 2
 calibration();
 }


 sensorValue0 = analogRead(sensorPin0);  //Lire la valeur du sensor 0
 sensorValue1 = analogRead(sensorPin1); //Lire la valeur du sensor 1
 sensorValue2 = analogRead(sensorPin2); //Lire la valeur du sensor 2
 sensorValeur0 = valeur0 (sensorZero0, sensorValue0 ); //Fonction valeur0 
 sensorValeur1 = valeur1 (sensorZero1, sensorValue1 ); //Fonction valeur1 
 sensorValeur2 = valeur2 (sensorZero2, sensorValue2 ); //Fonction valeur2 
 sensorTotal = calculeTotal ( sensorValeur1, sensorValeur2); 
 
total = total - data[readIndex];  //Pour la moyenne flotante 
//rial.print(readIndex);
//rial.print("/");
data[readIndex] = sensorTotal;
//rial.println(data[readIndex]);
total = total + data[readIndex];
readIndex = readIndex + 1;
if(readIndex >= 10) {
  readIndex = 0;
}
average = (total/10)* 0.048828125;  // 0.048828125 est la valeur de chaque valeur de la plage d'incrémentation du capteur

  delay(100); // On met un delais pour évité les problemes
 

 Serial.println(average); //Envois de la valeur du sensor)
 //Serial.print("Normal"); //test

}
int valeur0 (int x, int y){ //Declaration de la fonction pour crée la valeur 0 du capteur Haut Seul
  int resultat;
  resultat = x - y;  // SensorZero0 - SensorValue0 pour donner la valeur de resultat (capteur du haut = plus loin - plus proche distance)
  return resultat;  //renvois le resulta du calcule
  }
int valeur1 (int x, int y){ //Declaration de la fonction pour crée la valeur 0 du capteur Haut parrallele 
  int resultat;
  resultat = x - y;  // SensorZero1 - SensorValue1 pour donner la valeur de resultat (capteur du haut = plus loin - plus proche distance)
  return resultat;  //renvois le resulta du calcule
  }
 int valeur2 (int x, int y){ //Declaration de la fonction pour crée la valeur 0  du capteur bas Parrallele
  int resultat;  
  resultat = x - y;  // SensorZero2 - SensorValue2 pour donner la valeur de resultat (capteur du haut = plus loin - plus proche distance)
  return resultat;  //renvois le resulta du calcule
  }
 int calculeTotal (int x, int y){  // Calcule pour donner la L'epaisseur quand le styraine bouge
 int resultat;
 resultat = x + y;
 return resultat;
 }
 
 void calibration(){  // Fonction pour faire le 0 **** Activé quand le Styraine bouge et vérifié *******
 sensorZero0 = sensorValue0;
 sensorZero1 = sensorValue1;
 sensorZero2 = sensorValue2;
// Serial.print("Calibration"); //tett
 delay(100);
 
 }
 
