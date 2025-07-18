#include "RadMotora.h"
#include <Arduino.h>
#include <SCServo.h>
#include "GlobalnePromenljive.h"
#include <algorithm>

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
        Serial.print("ID: ");
        Serial.println(ID_u8[i]);
        Serial.print("Pozicija: ");
        Serial.println(pozicija_s16[i]);
        Serial.print("Zadata brzina: ");
        Serial.println(zadataBrzina_u16[i]);
        Serial.print("ACC: ");
        Serial.println(ACC_u8[i]);
    }

    servo.SyncWritePosEx(ID_u8, BROJ_MOTORA, pozicija_s16, zadataBrzina_u16, ACC_u8);
    //racunam vreme cekanja na osnovu brzine i pozicije

    int procitanePozicije[BROJ_MOTORA];//pravim niz koji cuva procitane pozicije
    for (int i = 0; i < BROJ_MOTORA; i++) {
      procitanePozicije[i] = servo.ReadPos(ID_u8[i]);
    }
    
    int razlikePozicije[BROJ_MOTORA];//pravim niz koji cuva razlike pozicija
    for (int i = 0; i < BROJ_MOTORA; i++) {
      razlikePozicije[i] = abs(vrednostPozicije[i] - procitanePozicije[i]);
    }
    
    int minBrzina = *std::min_element(zadataBrzina, zadataBrzina + BROJ_MOTORA);
    int maxRazlikaPozicija = *std::max_element(razlikePozicije, razlikePozicije + BROJ_MOTORA);
    int cekanje = (maxRazlikaPozicija / minBrzina) * 1000; // traje koliko traje kretanje
    //potrebne izmene nije dovoljno dobro za gledanje razlike u poziciji
    delay(cekanje);
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
