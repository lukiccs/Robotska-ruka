#include "GlobalnePromenljive.h"

typedef unsigned char u8;
typedef short s16;
typedef unsigned short u16;

String poruka;
int noviNiz[4];
int stariNiz[4] = {0, 0, 0, 0};
int pozicija[BROJ_MOTORA];
int brzina[BROJ_MOTORA];
float napon[BROJ_MOTORA];
int opterecenje[BROJ_MOTORA];
int ACC[5] = {0, 0, 0, 0, 0};
int ID[4] = {1, 2, 3, 4}; // ID motora, moze da se menja u zavisnosti od konfiguracije


SMS_STS servo;