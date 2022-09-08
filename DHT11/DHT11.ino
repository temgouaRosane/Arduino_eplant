#include <DHT.h>;
#include <Arduino.h>;
#include <WiFi.h>;
#include <Firebase_ESP_Client.h>;
#define DHT11_PIN 2
#include "addons/TokenHelper.h"
#include "addons/RTDBHelper.h"


//Define Firebase Data object
FirebaseData fbdo;
FirebaseAuth auth;
FirebaseConfig config;

// Insert Firebase project API Key
#define API_KEY "AIzaSyCjQI_9a85-CzV7tJLCq2DcPBnrYlXvEuk"

// Insert your network credentials
#define WIFI_SSID "Orange_Digital_Event"
#define WIFI_PASSWORD "Orange#20"

// Insert RTDB URLefine the RTDB URL */
#define DATABASE_URL "https://atomic-producer-361511-default-rtdb.firebaseio.com/" 

#define DHTTYPE DHT11
DHT dht(DHT11_PIN, DHTTYPE);

float temp, hum;
unsigned long sendDataPrevMillis = 0;
bool signupOK = false;

void setup(){
  Serial.begin(115200);
  WiFi.begin(WIFI_SSID, WIFI_PASSWORD);
  Serial.print("Connecting to Wi-Fi");
  while (WiFi.status() != WL_CONNECTED){
    Serial.print(".");
    delay(300);
  }
  Serial.println();
  Serial.print("Connected with IP: ");
  Serial.println(WiFi.localIP());
  Serial.println();
    /* Assign the api key (required) */
  config.api_key = API_KEY;
  
    /* Assign the RTDB URL (required) */
    config.database_url = DATABASE_URL;
    
    /* Sign up */
  if (Firebase.signUp(&config, &auth, "", "")){
    Serial.println("ok");
    signupOK = true;
  }
   config.token_status_callback = tokenStatusCallback; //see addons/TokenHelper.h
  
  Firebase.begin(&config, &auth);
  Firebase.reconnectWiFi(true);
  dht.begin();
  }


  void loop(){
    temp = dht.readTemperature();
    Serial.print(WiFi.status());
    hum = dht.readHumidity();
    if (Firebase.ready() && signupOK && (millis() - sendDataPrevMillis > 15000 || sendDataPrevMillis == 0)){
      Firebase.RTDB.setFloat(&fbdo, "test/float", temp);
       Serial.println(temp);
        Serial.println("PASSED");
       
        Serial.println("PATH: " + fbdo.dataPath());
        Serial.println("TYPE: " + fbdo.dataType());
      }
      else {
    Serial.println("FAILED");
    Serial.println("REASON: " + fbdo.errorReason());
    }
    delay(1000);
    }
