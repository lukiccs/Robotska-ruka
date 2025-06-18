#ifndef RADMOTORA_H
#define RADMOTORA_H

//deklaracija funkcija
void upisNaMotor(int vrednostPozicije[4], int ID[4], int zadataBrzina[4]);
int* citanjeSaMotoraPoz(int ID[4]);
int* citanjeSaMotoraBrzina(int ID[4]);
int* citanjeSaMotoraOpt(int ID[4]);
float* citanjeSaMotoraNap(int ID[4]);

#endif