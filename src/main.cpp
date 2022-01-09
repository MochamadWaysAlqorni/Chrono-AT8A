#include <Arduino.h>
#include <Wire.h>
#include <LiquidCrystal.h>
const int rs = 7, en = 6, d4 = 5, d5 = 4, d6 = 10, d7 = 9;
LiquidCrystal lcd(rs, en, d4, d5, d6, d7);

const int sensorPin1 = 2;
const int sensorPin2 = 3;
unsigned long waktu1;
unsigned long waktu2;
volatile int sensorState1 = 0;
volatile int sensorState2 = 0;

void masuk_ISR();
void keluar_ISR();

void setup()
{
  lcd.begin(16, 2);
  Serial.begin(9600);
  lcd.setCursor(0, 0);
  lcd.print("Mochamad Ways A.");
  lcd.setCursor(1, 1);
  lcd.print("CHRONOGRAPH V2");
  delay(2000);
  lcd.clear();
  lcd.setCursor(1, 0);
  lcd.print("CHRONOGRAPH V2");
  pinMode(sensorPin1, INPUT);
  pinMode(sensorPin2, INPUT);
  attachInterrupt(0, masuk_ISR, CHANGE);
  attachInterrupt(1, keluar_ISR, CHANGE);
}

void loop()
{
  unsigned long refresh = millis();
  if (refresh % 1000 == 0)
  {
    long waktusekarang = waktu2 - waktu1;
    float fps = ((7.2 / 30.48) * 1000000) / waktusekarang; //7.2cm space between the center of the sensors
    if (fps < 0 || fps > 10000)
    {
      lcd.setCursor(0, 1);
      lcd.print("  FPS : ");
      lcd.setCursor(8, 1);
      lcd.print("--.--    ");
    }
    else
    {
      lcd.setCursor(0, 1);
      lcd.print("  FPS : ");
      lcd.setCursor(8, 1);
      lcd.print("                ");
      lcd.setCursor(8, 1);
      lcd.print(fps);
    }
  }
}

void masuk_ISR()
{
  sensorState1 = digitalRead(sensorPin1);
  if (sensorState1 == HIGH)
  {
    waktu1 = micros();
  }
}

void keluar_ISR()
{
  sensorState2 = digitalRead(sensorPin2);
  if (sensorState2 == HIGH)
  {
    waktu2 = micros();
  }
}