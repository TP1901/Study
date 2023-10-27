int ampelRotPin = 13;
int ampelGelbPin = 11;
int ampelGruenPin = 9;


void setup() {
  pinMode(ampelRotPin, OUTPUT);
  pinMode(ampelGelbPin, OUTPUT);
  pinMode(ampelGruenPin, OUTPUT);
}

void loop() {
  // rot
  digitalWrite(ampelRotPin, HIGH);
  digitalWrite(ampelGelbPin, LOW);
  digitalWrite(ampelGruenPin, LOW);
  delay(5000);
  // rot-gelb
  digitalWrite(ampelRotPin, HIGH);
  digitalWrite(ampelGelbPin, HIGH);
  digitalWrite(ampelGruenPin, LOW);
  delay(3000);
  // gruen
  digitalWrite(ampelRotPin, LOW);
  digitalWrite(ampelGelbPin, LOW);
  digitalWrite(ampelGruenPin, HIGH);
  delay(5000);
  // gelb
  digitalWrite(ampelRotPin, LOW);
  digitalWrite(ampelGelbPin, HIGH);
  digitalWrite(ampelGruenPin, LOW);
  delay(3000);
}