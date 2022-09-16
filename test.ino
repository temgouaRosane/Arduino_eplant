#include <DHT.h>;
#include <HumiditeAir.h>;
#include <HumiditeSol.h>;
#include <ConfigAcessPoint.h>;
#include <PhDuSol.h>;
#include <Luminosite.h>;
#include <WiFiManager.h>;
int SensorPin= 26;
int pincapt = 12;
int capteur_lum = 2;
#define DHTPIN 13
#define DHTTYPE DHT11
#define ventilateur 5
//#define ruban 18

DHT dht(DHTPIN, DHTTYPE);


void setup() {
  Serial.begin(115200);
  //WiFiManager wm
  //bool res = configAccessPoint(wm);
  pinMode(SensorPin, INPUT);
  pinMode(ventilateur, OUTPUT);
  //pinMode(ruban, OUTPUT);

}

void loop (){
  float temp = dht.readTemperature();
  float humidite = dht.readHumidity();
  float ph =getPhSol(SensorPin);
  float humiditeSol = getHumiditeSol(pincapt);
  float luminosite = getLuminosite(capteur_lum);

  Serial.print("temperature:");
  Serial.print(temp);
  Serial.println("");
  Serial.print("humidite:");
  Serial.print(humidite);
  Serial.println("");
  if(temp>28.50){
  analogWrite(ventilateur, 255);
  }
else{
  analogWrite(ventilateur, 0);
}

  Serial.print("luminosite:");
  Serial.print(luminosite);
  Serial.println("");
//  digitalWrite(ruban,LOW);
//  delay(2000);
//  digitalWrite(ruban,HIGH);
//  delay(2000);
  Serial.print("humiditeSol:");
  Serial.print(humiditeSol);
  Serial.println("");
  Serial.print("ph:");
  Serial.print(ph);
  Serial.println("");
  
  
  delay(3000);
  
}
