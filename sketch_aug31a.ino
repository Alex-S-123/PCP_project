#include <WiFi.h>
 
const char* ssid = "OPU_server";  // Enter SSID here
const char* password = "12345678";  //Enter Password here

/* Put IP Address details */
IPAddress local_ip(192,168,1,1);
IPAddress gateway(192,168,1,1);
IPAddress subnet(255,255,255,0);

 
WiFiServer wifiServer(80);
 
void setup() {
 
  Serial.begin(115200);
 
  delay(1000);
 
  WiFi.softAP(ssid, password);
  WiFi.softAPConfig(local_ip, gateway, subnet);
  wifiServer.begin();
}
 
void loop() {
 
  WiFiClient client = wifiServer.available();
  bool was_connected = false;
 
  if (client) {
    Serial.println("Client connected");
    while (client.connected()) {
      String s = "";
      while (client.available()>0) {
        char c = client.read();
        s += c;
        was_connected = true;
      }
      if(was_connected){
        was_connected = false;
        Serial.println(s);
      }
      //here is place for other code
 
      delay(10);
    }
    
    client.stop();
    Serial.println("Client disconnected");
 
  }
}
