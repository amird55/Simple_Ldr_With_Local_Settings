#define LdrPin A0
#define LedPin D2

void setup() {
  Serial.begin(9600);
  pinMode(LedPin,OUTPUT);
  WifiSetup();
}

void loop() {
  int LdrVal = analogRead(LdrPin);
  Serial.println(LdrVal);
  int LedVal=map(LdrVal,0,1023,255,0);
  analogWrite(LedPin,LedVal);
  wifi_loop();
}
