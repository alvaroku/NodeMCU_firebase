
//https://www.taloselectronics.com/blogs/tutoriales/como-conectar-nodemcu-con-firebase

#include <WiFi.h>
#include <FirebaseESP32.h>
//#include <FirebaseESP8266.h>
//#include <ESP8266WiFi.h>
// Set these to run example.
#define FIREBASE_HOST "smart-home-345b3-default-rtdb.firebaseio.com"
#define FIREBASE_AUTH "rf2ijT8voFtI6KroUH0bYLQfck2Zi1Qpj5kIk9yy"
#define WIFI_SSID "Telcel-HUAWEI_B311_A734"
#define WIFI_PASSWORD "EG9Q2N8453Q"
int Led = 4;

volatile bool estado = false;
FirebaseData firebaseData;
String path = "/smart-home/relay/estado";

void setup() {
  Serial.begin(9600);
  pinMode(21, OUTPUT);
  // connect to wifi.
  WiFi.begin(WIFI_SSID, WIFI_PASSWORD);
  Serial.print("connecting");
  while (WiFi.status() != WL_CONNECTED) {
    Serial.print(".");
    delay(500);
  }
  digitalWrite(21,HIGH);
  Serial.println();
  Serial.print("connected: ");
  Serial.println(WiFi.localIP());

  Firebase.begin(FIREBASE_HOST, FIREBASE_AUTH);
  Firebase.reconnectWiFi(true);

  pinMode(Led, OUTPUT);

}


void loop() {
  actualizar_estado();
  if(estado)
  {
    digitalWrite(Led, HIGH);
  }
  else
  {
    digitalWrite(Led, LOW);
  }
  delay(2000);
}
void actualizar_estado()
{
    
  if (Firebase.getBool(firebaseData, path))
    {
      Serial.println("PASSED");
      Serial.println("PATH: " + firebaseData.dataPath());
      Serial.println("TYPE: " + firebaseData.dataType());
      Serial.println("ETag: " + firebaseData.ETag());
      Serial.print("VALUE: ");
      estado=firebaseData.boolData();
      Serial.println(estado);
      Serial.println("------------------------------------");
      Serial.println();
    }
    else
    {
      Serial.println("FAILED: "+path);
      Serial.println("REASON: " + firebaseData.errorReason());
      Serial.println("------------------------------------");
      Serial.println();
    }
}
