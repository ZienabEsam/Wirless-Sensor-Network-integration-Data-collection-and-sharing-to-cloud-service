//This ESP is set to Staion/AcessPoint mode 
//first it set to be an AcessPoint for the station to post data
//then turns to be the staion mode for publishing data on the cloud
// Iot platform ThingSpeak :) 
//By setting this ESP as AP/STA mode it's consedered more like a coordinator
//In the wireless sensor network

#include <ESP8266WiFi.h>
#include <ESP8266WebServer.h>
// IoT platform Credentials
String apiKey = "429KCC9N7VZ4DZHL";
const char* logServer = "api.thingspeak.com";

// Internet router credentials
const char* ssid = "ESP-AP";
const char* password = "22446688";

ESP8266WebServer server(80);

void setup() {
}
// Handling the / root web page from my server

void setupAccessPoint(){
  Serial.println("** SETUP ACCESS POINT **");
  Serial.println("- disconnect from any other modes");
  WiFi.disconnect();
  Serial.println("- start ap with SID: "+ String(ssid));
  WiFi.softAP(ssid, password);
  IPAddress myIP = WiFi.softAPIP();
  Serial.print("- AP IP address is :");
  Serial.print(myIP);
  setupServer();
}

void setupServer(){
  Serial.println("** SETUP SERVER **");
  Serial.println("- starting server :");
  server.on("/", handle_index);
  server.on("/channels", handle_feed);
  server.begin();
};
void handle_index() {
  server.send(200, "text/plain", "Get out from my server!");
}

// Handling the /feed page from my server
void handle_feed() {
  String temperature2 = server.arg("temperature");
  String humidity2 = server.arg("humidity");

  server.send(200, "text/plain", "This is response to client");
  setupStMode(temperature2, humidity2);
}

void setupStMode(String t, String v){
  Serial.println("** SETUP STATION MODE **");
  Serial.println("- disconnect from any other modes");
  WiFi.disconnect();
  Serial.println();
  Serial.println("- connecting to Home Router SID: **********");
  WiFi.begin("El-Gohary", "42060222");
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  Serial.println();
  Serial.println("- succesfully connected");
  Serial.println("- starting client");
  
  WiFiClient client;

  Serial.println("- connecting to Database server: " + String(logServer));
  if (client.connect(logServer, 80)) {
    Serial.println("- succesfully connected");
    String postStr = apiKey;
    postStr += "&field1=";
    postStr += String(t);
    postStr += "&field2=";
    postStr += String(v);
    postStr += "\r\n\r\n";
    Serial.println("- sending data...");
    client.print("POST /update HTTP/1.1\n");
    client.print("Host: api.thingspeak.com\n");
    client.print("Connection: close\n");
    client.print("X-THINGSPEAKAPIKEY: " + apiKey + "\n");
    client.print("Content-Type: application/x-www-form-urlencoded\n");
    client.print("Content-Length: ");
    client.print(postStr.length());
    client.print("\n\n");
    client.print(postStr);
  }
  client.stop();
  Serial.println("- stopping the client");
  /** If your ESP does not respond you can just
  *** reset after each request sending 
  Serial.println("- trying reset");
  ESP.reset();
  **/
  delay(20000);
}

void loop() {
  //congfiguring the ESP as Acess Point / Station mode
  Serial.begin(115200);
  WiFi.mode(WIFI_AP_STA);
  setupAccessPoint();
  server.handleClient();
}
