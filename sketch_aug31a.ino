#include <WiFi.h>
 
const char* ssid = "ESP32";  // Enter SSID here
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
  delay(100);
 
  Serial.println("Connected to the WiFi network");
  Serial.println(WiFi.localIP());
 
  wifiServer.begin();
}
 
void loop() {
 
  WiFiClient client = wifiServer.available();
  bool was_connected = false;
 
  if (client) {
 
    while (client.connected()) {
 
      while (client.available()>0) {
        char c = client.read();
        Serial.print(c);
        client.write(c);
        was_connected = true;
      }
      if(was_connected){
        client.write('0');
        Serial.println();
        was_connected = false;
      }
 
      delay(10);
    }
    
    client.stop();
    Serial.println("Client disconnected");
 
  }
}
