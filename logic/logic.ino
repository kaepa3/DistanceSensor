#include <Wire.h>
#include <VL53L0X.h>
#include <LiquidCrystal_I2C.h>

LiquidCrystal_I2C lcd (0x27,16,2);

VL53L0X sensor;

void setup() {
  // put your setup code here, to run once:
  setupLcd();

  setupDistanceSensor();
}

void setupDistanceSensor(){
  Serial.begin(9600);
  Wire.begin();
  
  sensor.setTimeout(500);
  if (!sensor.init())
  {
    Serial.println("Failed to detect and initialize sensor!");
    while (1) {}
  }
  sensor.startContinuous();
}

void setupLcd(){
  lcd.init();
  lcd.backlight();
  lcd.clear();  
  lcd.setCursor(0, 0);
  lcd.print("start");
}

void loop() {
  // put your main code here, to run repeatedly:
  int distance = sensor.readRangeContinuousMillimeters();
  if (sensor.timeoutOccurred()) { Serial.print(" TIMEOUT"); }
  display(distance);

  
  delay(1000);
  
}
void display(int distance){
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("hello world");
  lcd.setCursor(0, 1);
  lcd.print("distance:");
  lcd.setCursor(10,1);
  lcd.print(distance);

  Serial.print(distance);
  Serial.println();
}
