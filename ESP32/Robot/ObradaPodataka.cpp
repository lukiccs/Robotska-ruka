#include "ObradaPodataka.h"
#include <Arduino.h>
#include "RadMotora.h"
#include "GlobalnePromenljive.h"
//dodati fajl u kome se nalazi upisNaMotor, citanjeSaMotoraPoz, citanjeSaMotoraBrzina, citanjeSaMotoraOpt, citanjeSaMotoraNap

void obradaNiza(){
//Od stringa pravi niz intigera i radi provere
  char* token = strtok((char*)poruka.c_str(), " ");//radi formatiranje podataka koji dolaze iz MATLAB
  int i = 0;
  while(token != NULL && i < 4){
    noviNiz[i] = atoi(token);
    token = strtok(NULL, " ");
    i = i + 1;
  }
  noviNiz[1] = abs(noviNiz[1] - 2048); // pomeren middle point pa mora da se sredi
  // upisNaMotor(abs(noviNiz[3] - 2048));

  for(int j = 0; j < 4; j++){//samo prebacivanje radi dalje provere
    stariNiz[j] = noviNiz[j];
  }
}