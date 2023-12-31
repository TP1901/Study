//Determine Code
#include <ESP8266WiFi.h>
#include <ESP8266HTTPClient.h>
#include <WiFiClient.h>

//urls
String GetURL = "http://210301.de/iot/ws/3/a.txt";

//pin settings
const int buttonPin = D8;
int buttonValue = 0;

const int pinRed   = D3;
const int pinGreen = D1;

//wifi settings
const char* ssid = "coding@HSNR";
const char* pwd  = "CDHSNR23";

void setup() {
  //start serial monitor
  Serial.begin(57600);
  delay(10);

  //pinMode
  pinMode(buttonPin, INPUT);
  pinMode(pinRed, OUTPUT);
  pinMode(pinGreen, OUTPUT);

  //Aufruf der Methoden
  connectWiFi();
  startupBlink();
}

void loop() {
  //read button value
  buttonValue = digitalRead(buttonPin);
  Serial.print("Button: ");
  
  //print ON or OFF
  if(buttonValue == 0) {
    Serial.println("OFF");
  }
  else {
    Serial.println("ON");
  }

  //readout the entry from webserver
  if(WiFi.status() == WL_CONNECTED) {
    WiFiClient client;
    HTTPClient http;
    String payload;
    int httpGETCode; 

    http.begin(client, GetURL);

    httpGETCode = http.GET();
    Serial.print("(GET) HttpCode: ");
    Serial.println(httpGETCode);

    if(httpGETCode == 200) {
      payload = http.getString();
      Serial.print("(GET) Payload: ");
      Serial.println(payload);
    }

    http.end();

    //change colore due to button
    if(payload == "gruen") {
      digitalWrite(pinRed, LOW);
      digitalWrite(pinGreen, HIGH);
    }
    else if(payload == "rot") {
      digitalWrite(pinRed, HIGH);
      digitalWrite(pinGreen, LOW);
    }

    //set value on webserver like button action
    if(buttonValue == 0) {
      http.begin(client, "http://210301.de/iot/ws/3/ws.php?p=gruen");
      httpGETCode = http.GET();

      Serial.print("(GET) HttpCode: ");
      Serial.println(httpGETCode);
      Serial.println("----------------");

      http.end();
    }
    else if(buttonValue == 1) {
      http.begin(client, "http://210301.de/iot/ws/3/ws.php?p=rot");
      httpGETCode = http.GET();

      Serial.print("(GET) HttpCode: ");
      Serial.println(httpGETCode);
      Serial.println("----------------");

      http.end();
    }

    delay(1000);
  }
}
//test method
void startupBlink(){
  
  digitalWrite(pinRed, HIGH);
  digitalWrite(pinGreen, LOW);

  delay(500);
  
  digitalWrite(pinRed, LOW);
  digitalWrite(pinGreen, HIGH);

  delay(500);

  digitalWrite(pinRed, LOW);
  digitalWrite(pinGreen, LOW);
  
}
//connect WiFi
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
  Serial.println("----------------");
}

