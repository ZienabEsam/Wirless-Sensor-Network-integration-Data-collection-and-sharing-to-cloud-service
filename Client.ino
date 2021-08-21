
/*This ESP-01 has bees set up to be a Station to collect 
 * sensor data and 
 * send it to a coordinator also an ESP-01 to be published on the 
 * cloud usng the thingspeak IoT platform, so this ESP is more to 
 * repreesent a sensor layer can be combined with another
 * sensor holding an ESP8266 module to form a mesh network
*/
#include <ESP8266HTTPClient.h>
#include <ESP8266WiFi.h>
#include <ESP8266WiFiGeneric.h>
#include <ESP8266WiFiSTA.h>
#include <ESP8266WiFiType.h>
#include <WiFiClient.h>
#include <WiFiClientSecure.h>
#include <WiFiServer.h>
#include <WiFiUdp.h>

/*I have used a DHT11 sensor it's a Temperature && Humidity sensor
Connected on GPIO02 GPIO is shorf of (General purpose I/O) pin
used to connect sensors to the ESP8266 series
*/
//Defining sensor parameters
#include <dht.h>
#define DHT11_PIN 2
//creating a constructor of the DHT class to make use of the functions
dht sensor1;
float temperature,humidity;

//Defining Internet Parameters
//The Network the ESP will be connected to
const char* WLAN_SSID = "ESP-AP";
const char* WLAN_PASS = "22446688";
IPAddress ip = (192,168,0,103);
IPAddress gateway = (192,168,0,103);
IPAddress subnet = (255,255,255,0);
int counter = 0 ;
int sleepInterval = 5;
const char* hostName = "http://192.168.0.103/channels";
int port = 80 ;
String data ;
 WiFiClientSecure client;

 //===========================================================
 
void setup(){
  //deleting all previous configuration
  ESP.eraseConfig();
// setting pin (GPIO02) to recieve the temperature and humidity input
  pinMode(2,INPUT);
  digitalRead(2);
  
  }
  
void loop(){
  
  Serial.begin(115200);
  delay(100);
   //Configuring the ESP to a Staion Mode
  WiFi.mode(WIFI_STA);
  WiFi.config(ip,gateway,subnet);
  WiFi.begin(WLAN_SSID,WLAN_PASS);
  Serial.println("Connecting to Acess point");
  delay(1000);
  while(WiFi.status() != WL_CONNECTED){
    Serial.print("Authinticating in process,..");
    if(counter > 200){
      Serial.println("Unable to connect to Acess Point, going to sleep");

      hibernate(sleepInterval);
      }
      delay(200);
      counter++;
      
    }
    //Serial view of temperature and humidity
    Serial.println("Connected succefully to Acess point");
    delay(1000);
    Serial.println("Collecting sensor data,..");
    collectSensorData();
    //sending "GET" request to the sever
    sendGETRequest();
    Serial.println("Request has been sent");
    Serial.println("I have finished my Job going back to sleep, :)");
    Serial.println("ZZZZZZZZZZzzzzzzz");
    hibernate(sleepInterval);
  }
   void collectSensorData(){
      delay(2000);
      digitalRead(2);
      sensor1.read11(2);
      temperature = sensor1.temperature;
      humidity = sensor1.humidity;
      Serial.println("Temperature no is :");
      Serial.println(temperature,1);
      Serial.println("Humidity now is :");
      Serial.println(humidity,1);
                    data = "Temperature : ";
                    data += String(temperature);
                    data += "Humidity : ";
                    data += String(humidity);
     
      }

     void sendGETRequest(){
      Serial.println("Connecting to Host");
      Serial.println(hostName);
      if(!client.connect(hostName,port)){
        Serial.println("Failed To Connect");
        return;
        }else{
          Serial.println("Sucessfully connected to host" + String(hostName));
          }
         HTTPClient http;
         http.begin(hostName);
         http.addHeader("Content-Type:","application/x-www-form-urlencoded");
         http.POST(data);
         http.writeToStream(&Serial);
         http.end();
                  
        }
  void hibernate(int PInterval){
      WiFi.disconnect();
      ESP.deepSleep(10 * 600000 * PInterval,WAKE_RFCAL);
      delay(200);
      }
