#define LdrPin A0
#define LedPin D2

int LdrVal;
int LedVal;
int MapDir=1;
void setup() {
  Serial.begin(9600);
  pinMode(LedPin,OUTPUT);
  WifiSetup();
}

void loop() {
  LdrVal = analogRead(LdrPin);
  Serial.println(LdrVal);
  if(MapDir == 1){
    LedVal=map(LdrVal,0,1023,0,255);
  } else {
    LedVal=map(LdrVal,0,1023,255,0);
  }
  analogWrite(LedPin,LedVal);
  wifi_loop();
}
