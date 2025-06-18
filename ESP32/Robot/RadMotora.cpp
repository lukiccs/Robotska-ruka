#include "RadMotora.h"
#include <Arduino.h>
#include <SCServo.h>
#include "GlobalnePromenljive.h"

typedef unsigned char u8;
typedef short s16;
typedef unsigned short u16;

void upisNaMotor(int vrednostPozicije[4], int ID[4], int zadataBrzina[4]) {
    // Upisujem vrednosti na motor
    u8 ID_u8[4];
    s16 pozicija_s16[4];
    u16 zadataBrzina_u16[4];
    //Radim typecast jer su vrednosti koje se upisuju na motor u razlicitim tipovima
    for (int i = 0; i < 4; i++) {
        ID_u8[i] = (u8)ID[i];
        pozicija_s16[i] = (s16)vrednostPozicije[i];
        zadataBrzina_u16[i] = (u16)zadataBrzina[i];
    }

    servo.SyncWritePosEx(ID_u8, brojMotora, pozicija_s16, zadataBrzina_u16, ACC);
    // int cekanje = ((vrednostPozicije - servo.ReadPos(1)) / 7000) * 1000; // traje koliko traje kretanje
    //mora se dodati racun za cekanje
    delay(1000); // Ovo je samo primer, treba izracunati realno vreme cekanja
}
//odraditi return pointera na pocetak niza a onda raditi sa tim pointerom kroz stack
int* citanjeSaMotoraPoz(int ID[4]){
  //citam vrednosti pozicije, brzine, napona, i opterecenja
  for (int i = 0; i < 4; i++)
  {
    pozicija[i] = servo.ReadPos(ID[i]);
  }
  return pozicija;
}

int* citanjeSaMotoraBrzina(int ID[4]){
  //citam vrednosti pozicije, brzine, napona, i opterecenja
  for (int i = 0; i < 4; i++)
  {
    brzina[i] = servo.ReadSpeed(ID[i]);
  }
  return brzina;
}

int* citanjeSaMotoraOpt(int ID[4]){
  //citam vrednosti pozicije, brzine, napona, i opterecenja
  for (int i = 0; i < 4; i++)
  {
    opterecenje[i] = servo.ReadLoad(ID[i]);
  }  
  return opterecenje; //opterecenje se dobija u opsegu od -1024 do 1024 gde je od 0 do 1024 cw, a ispod 0 ccw
}

float* citanjeSaMotoraNap(int ID[4]){
  //citam vrednosti pozicije, brzine, napona, i opterecenja
  for (int i = 0; i < 4; i++)
  {
    napon[i] = servo.ReadVoltage(ID[i]);
    napon[i] *= 0.1; //mnozim sa 0.1 jer je svaka jedinica koja se cita 0.1V
  } 
  return napon;
}
