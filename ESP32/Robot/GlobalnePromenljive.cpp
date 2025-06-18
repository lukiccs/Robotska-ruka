#include "GlobalnePromenljive.h"

typedef unsigned char u8;
typedef short s16;
typedef unsigned short u16;

String poruka;
int noviNiz[4];
int stariNiz[4] = {0, 0, 0, 0};
int pozicija[4];
int brzina[4];
float napon[4];
int opterecenje[4];
u8 brojMotora = 4;
u8 ACC[5] = {150, 150, 150, 150, 150};
SMS_STS servo;