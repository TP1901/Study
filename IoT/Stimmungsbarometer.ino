//Mood-Light

#include <ESP8266WiFi.h>
#include <ESP8266HTTPClient.h>
#include <WiFiClient.h>

//urls
String url = "URL-Webserver";

//pin settings
const int pinRed   = D5;
const int pinYellow  = D3;
const int pinGreen = D1;

//wifi settings
const char* ssid = "Name";
const char* pwd  = "Passwort";

void setup() {
  Serial.begin(9600);
  delay(10);

  pinMode(pinRed, OUTPUT);
  pinMode(pinYellow, OUTPUT);
  pinMode(pinGreen, OUTPUT);

  connectWiFi();
}

void loop() {
  if(WiFi.status() == WL_CONNECTED) {
    WiFiClient client;
    HTTPClient http;
    String payload;

    http.begin(client, url);

    int httpCode = http.GET();
    Serial.print("HttpCode: ");
    Serial.println(httpCode);

    if(httpCode == 200) {
      payload = http.getString();
      Serial.print("Payload: ");
      Serial.println(payload);
    }
    http.end();

    if(payload == "gruen") {
      digitalWrite(pinRed, LOW);
      digitalWrite(pinYellow, LOW);
      digitalWrite(pinGreen, HIGH);
    }
    else if(payload == "rot") {
      digitalWrite(pinRed, HIGH);
      digitalWrite(pinYellow, LOW);
      digitalWrite(pinGreen, LOW);
    }
    else if(payload == "gelb") {
      digitalWrite(pinRed, LOW);
      digitalWrite(pinYellow, HIGH);
      digitalWrite(pinGreen, LOW);
    }
    else {
      digitalWrite(pinRed, LOW);
      digitalWrite(pinYellow, LOW);
      digitalWrite(pinGreen, LOW);
    }

    delay(3000);
  }
}

void connectWiFi() {
  Serial.println("");
  Serial.print("Connecting to ");
  Serial.println(ssid);
  
  WiFi.begin(ssid, pwd);
  while (WiFi.status() != WL_CONNECTED) {
    // retry attempt every 500ms
    delay(500);
    Serial.print(".");
  }
  
  Serial.println("");
  Serial.println("WiFi connected!");
  Serial.print("IP address: ");
  Serial.println(WiFi.localIP());
}
