#include "RadMotora.h"
#include <Arduino.h>
#include <SCServo.h>
#include "GlobalnePromenljive.h"

typedef unsigned char u8;
typedef short s16;
typedef unsigned short u16;

void upisNaMotor(int vrednostPozicije[4], int ID[4], int zadataBrzina[4]) {
    // Upisujem vrednosti na motor
    u8 ID_u8[BROJ_MOTORA];
    s16 pozicija_s16[BROJ_MOTORA];
    u16 zadataBrzina_u16[BROJ_MOTORA];
    u8 ACC_u8[BROJ_MOTORA];
    //Radim typecast jer su vrednosti koje se upisuju na motor u razlicitim tipovima
    for (int i = 0; i < BROJ_MOTORA; i++) {
        ID_u8[i] = (u8)ID[i];
        pozicija_s16[i] = (s16)vrednostPozicije[i];
        zadataBrzina_u16[i] = (u16)zadataBrzina[i];
        ACC_u8[i] = (u8)ACC[i];
    }

    servo.SyncWritePosEx(ID_u8, BROJ_MOTORA, pozicija_s16, zadataBrzina_u16, ACC_u8);
    // int cekanje = ((vrednostPozicije - servo.ReadPos(1)) / 7000) * 1000; // traje koliko traje kretanje
    //mora se dodati racun za cekanje
    delay(1000); // Ovo je samo primer, treba izracunati realno vreme cekanja
}
//odraditi return pointera na pocetak niza a onda raditi sa tim pointerom kroz stack
int* citanjeSaMotoraPoz(int ID[BROJ_MOTORA]){
  //citam vrednosti pozicije, brzine, napona, i opterecenja
  for (int i = 0; i < BROJ_MOTORA; i++)
  {
    pozicija[i] = servo.ReadPos(ID[i]);
  }
  return pozicija;
}

int* citanjeSaMotoraBrzina(int ID[BROJ_MOTORA]){
  //citam vrednosti pozicije, brzine, napona, i opterecenja
  for (int i = 0; i < BROJ_MOTORA; i++)
  {
    brzina[i] = servo.ReadSpeed(ID[i]);
  }
  return brzina;
}

int* citanjeSaMotoraOpt(int ID[BROJ_MOTORA]){
  //citam vrednosti pozicije, brzine, napona, i opterecenja
  for (int i = 0; i < BROJ_MOTORA; i++)
  {
    opterecenje[i] = servo.ReadLoad(ID[i]);
  }  
  return opterecenje; //opterecenje se dobija u opsegu od -1024 do 1024 gde je od 0 do 1024 cw, a ispod 0 ccw
}

float* citanjeSaMotoraNap(int ID[BROJ_MOTORA]){
  //citam vrednosti pozicije, brzine, napona, i opterecenja
  for (int i = 0; i < BROJ_MOTORA; i++)
  {
    napon[i] = servo.ReadVoltage(ID[i]);
    napon[i] *= 0.1; //mnozim sa 0.1 jer je svaka jedinica koja se cita 0.1V
  } 
  return napon;
}
