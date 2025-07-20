#include "ObradaPodataka.h"
#include <Arduino.h>
#include "RadMotora.h"
#include "GlobalnePromenljive.h"
//dodati fajl u kome se nalazi upisNaMotor, citanjeSaMotoraPoz, citanjeSaMotoraBrzina, citanjeSaMotoraOpt, citanjeSaMotoraNap

void obradaNiza(String poruka){
//Od stringa pravi niz intigera i radi provere
  char* token = strtok((char*)poruka.c_str(), " ");//radi formatiranje podataka koji dolaze iz MATLAB
  int i = 0;
  while(token != NULL && i < 4){
    noviNiz[i] = atoi(token);
    token = strtok(NULL, " ");
    i = i + 1;
  }
  noviNiz[2] = abs(noviNiz[2] - 2048); // pomeren middle point pa mora da se sredi
  // upisNaMotor(abs(noviNiz[3] - 2048));
  int zadataBrzina[4] = {1000, 1000, 1000, 1000}; //privremeno stavljama dok ne uradim PID

  upisNaMotor(noviNiz, ID, zadataBrzina); // upisujem vrednosti na motor
  // realnu brizinu treba izracunati na osnovu razlike u poziciji i vremenu iz PID
  // max brzina ce se racunati na osnovu opterecenosti ruke da bih imao obrtnog momenta

  for(int j = 0; j < 4; j++){//samo prebacivanje radi dalje provere
    stariNiz[j] = noviNiz[j];
  }
}

float obradaOpterecenja(float opterecenje){
  
  // Ova funkcija treba da obradi sirove vrednosti i da vrati obrtni moment
  //moram da izvucem raw opterecenje i da vidim da ga skaliram prema max opterecenju(20kg/cm)
  //ali zelim da posle to ubacim u proracun opterecenja i da tako dobijem preko struje, napona tj snage i opterecenja brzinu
  //servo daje opterecenje u opsegu od -2048 do 2048(ako je opterecenje negativno onda je motor zapravo rasterecen)
}