#include <SCServo.h>
#include <WiFi.h>

// definisem sifru i ime wifi mreze
const char* ssid = "Yettel_1C9368";
const char* password = "cT9zCSH7";

int noviNiz[4];
int stariNiz[4] = {0, 0, 0, 0};

int pozicija;
int brzina;
int napon;
int opterecenje;


String poruka;
WiFiServer serverWIFI(1234);
SMS_STS servo_1;

void setup() {
  Serial.begin(115200);
  Serial2.begin(1000000, SERIAL_8N1, 16, 17);
  servo_1.pSerial = &Serial2;
  WiFiSetup();
  delay(1000);


}

void loop() {
  // Serial.println("MRK");
  WiFiPrijem();
}

void WiFiSetup(){
// Pravi i proverava povezanost preko WiFi
  WiFi.begin(ssid, password);
  Serial.print("Povezuje se...");
  while(WiFi.status() != WL_CONNECTED){
    delay(500);
    Serial.print(".");
  }
  Serial.println("WIFI Povezan!");
  Serial.println(WiFi.localIP());
  serverWIFI.begin();
}

void WiFiPrijem(){
// Prima podatke iz MATLAB-a
  WiFiClient client = serverWIFI.accept();
  if (client) {
    while (client.connected()) {
      if (client.available()) {
        poruka = client.readStringUntil('\n');
        // Serial.println("Primljeno: " + poruka);
        obradaNiza();
        client.println("nastavi");//Handshake protocol
      }
    }
    client.stop();
  }
}

void obradaNiza(){
//Od stringa pravi niz intigera i radi provere
  char* token = strtok((char*)poruka.c_str(), " ");//radi formatiranje podataka koji dolaze iz MATLAB
  int i = 0;
  while(token != NULL && i < 4){
    noviNiz[i] = atoi(token);
    token = strtok(NULL, " ");
    i = i + 1;
  }

  for(int j = 0; j < 4; j++){ //Provera najblizeg puta, da li je preko pola ili nije
    int d = noviNiz[j] - stariNiz[j];
    // if (d > 2048) {
    //   noviNiz[j] -= 4096;
    // }
    if (d < -2048) {
      noviNiz[j] += 4096;
    }
    noviNiz[j] = (stariNiz[j] + (noviNiz[j] - stariNiz[j]) + 4096) % 4096;//normalizuje vrednost
  }

  for(int j = 0; j < 4; j++){ //ispis za proveru
    Serial.print("stari: ");
    Serial.print(stariNiz[j]);
    Serial.print(" novi: ");
    Serial.print(noviNiz[j]);
    Serial.print(" stvarna vrednost: : ");
    Serial.print(citanjeSaMotoraPoz());
    Serial.print(" brzina: ");
    Serial.print(citanjeSaMotoraBrzina());
    Serial.print(" opterecenje: ");
    Serial.print(citanjeSaMotoraOpt());
    Serial.print(" napon: ");
    Serial.println(citanjeSaMotoraNap());
  }

  upisNaMotor(noviNiz[3]);

  for(int j = 0; j < 4; j++){//samo prebacivanje radi dalje provere
    stariNiz[j] = noviNiz[j];
  }
}

void upisNaMotor(int vrednostPozicije){
// Upisujem vrednosti na motor
  servo_1.WritePosEx(1, vrednostPozicije, 7000);
  int cekanje = ((vrednostPozicije - citanjeSaMotoraPoz())/7000)*1000 + 100;//traje koliko traje kretanje
  delay(cekanje);
}

int citanjeSaMotoraPoz(){
  //citam vrednosti pozicije, brzine, napona, i opterecenja
  pozicija = servo_1.ReadPos(1);
  return pozicija;
}

int citanjeSaMotoraBrzina(){
  //citam vrednosti pozicije, brzine, napona, i opterecenja
  brzina = servo_1.ReadSpeed(1);
  return brzina;
}

int citanjeSaMotoraOpt(){
  //citam vrednosti pozicije, brzine, napona, i opterecenja
  opterecenje = servo_1.ReadLoad(1);
  return opterecenje;//opterecenje se dobija u opsegu od -1024 do 1024 gde je od 0 do 1024 cw, a ispod 0 ccw
}

int citanjeSaMotoraNap(){
  //citam vrednosti pozicije, brzine, napona, i opterecenja
  napon = servo_1.ReadVoltage(1);
  return napon * 0.1;//mnozim sa 0.1 jer je svaka jedinica koja se cita 0.1V
}

//Dodati 4096 u zagradi gde se zadaje pozicija WritePosEx(1, x+4096....);
//OBAVEZNO PROVERITI PRELAZENJE PREKO NULE IMA NA GOOGLE










  


