#ifndef GLOBALNEPROMENLJIVE_H
#define GLOBALNEPROMENLJIVE_H

#include <SCServo.h>

typedef unsigned char u8;
typedef short s16;
typedef unsigned short u16;

//deklaracija globalnih promenljivih
extern String poruka;
extern int noviNiz[4];
extern int stariNiz[4];
extern int pozicija[4];
extern int brzina[4];
extern float napon[4];
extern int opterecenje[4];
extern u8 brojMotora;
extern u8 ACC[5];

//deklaracija objekta servo
extern SMS_STS servo;

#endif