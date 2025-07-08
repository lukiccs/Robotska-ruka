#ifndef GLOBALNEPROMENLJIVE_H
#define GLOBALNEPROMENLJIVE_H

#include <SCServo.h>

typedef unsigned char u8;
typedef short s16;
typedef unsigned short u16;
// #define BROJ_MOTORA 4
const u8 BROJ_MOTORA = 2;

//deklaracija globalnih promenljivih
extern int noviNiz[4];
extern int stariNiz[4];
extern int pozicija[BROJ_MOTORA];
extern int brzina[BROJ_MOTORA];
extern float napon[BROJ_MOTORA];
extern int opterecenje[BROJ_MOTORA];
extern int ACC[5];
extern int ID[4]; // ID motora, moze da se menja u zavisnosti od konfiguracije

//deklaracija objekta servo
extern SMS_STS servo;

#endif