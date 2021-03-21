#include <LiquidCrystal.h>
const int rs = 12, en = 11, d4 = 5, d5 = 4, d6 = 3, d7 = 2;
LiquidCrystal lcd(rs, en, d4, d5, d6, d7);

int rainPin = A0;
int greenLED = 6;
int redLED = 7;
// you can adjust the threshold value - max is 1023
int thresholdValue = 1000;

int lightPin = A1;

void setup(){
  lcd.begin(16, 2);
  lcd.setCursor(0,0);
  lcd.print("Starting");
  
  pinMode(rainPin, INPUT);
  pinMode(greenLED, OUTPUT);
  pinMode(redLED, OUTPUT);
  digitalWrite(greenLED, LOW);
  digitalWrite(redLED, LOW);
  Serial.begin(9600);
  lcd.clear();
}

void loop() {
  // read the input on analog pin 1:
  int lightValue = analogRead(lightPin);

  if(lightValue > 150){
    // read the input on analog pin 0:
    int sensorValue = analogRead(rainPin);
    lcd.clear();
    lcd.setCursor(0,0);
    lcd.print(sensorValue);
    lcd.setCursor(0,1);
    //Serial.print(sensorValue);
    
    int t = millis()/3600000;
    if(sensorValue < thresholdValue || t < 48){
      lcd.setCursor(7,0);
      lcd.print(t);
      lcd.setCursor(0,1);
      lcd.print("Hrs since reset");
      digitalWrite(redLED, LOW);
      digitalWrite(greenLED, HIGH);
      delay(1000);
      digitalWrite(greenLED, LOW);
      delay(59000);
    }
    else {
      lcd.print("Time to Water!");
      digitalWrite(redLED, HIGH);
      digitalWrite(greenLED, LOW);
      delay(30000);
    }
  }
  else {
    //lcd.clear();
    digitalWrite(redLED, LOW);
    digitalWrite(greenLED, LOW);
    delay(1000);
  }
  
}
