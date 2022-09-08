#include <WiFiManager.h>
void setup() {
  
  // put your setup code here, to run once:
  WiFi.mode(WIFI_STA);
  Serial.begin(115200);
WiFiManager wm;
bool res ;
//res = wm.autoConnect();
res =  wm.autoConnect("AutoConnectAP","password");
Serial.println(res);
if(!res){
  Serial.println("Failed to connect");
}
else {
  Serial.println("success");
  }
}

void loop() {
  // put your main code here, to run repeatedly:

}
