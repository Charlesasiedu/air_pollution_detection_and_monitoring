#include <LiquidCrystal.h>
#include <DHT.h>

// initialize the LCD library
LiquidCrystal lcd(4, 5, 6, 7, 8, 9);

// initialize the DHT sensor
#define DHTPIN 2
#define DHTTYPE DHT11
DHT dht(DHTPIN, DHTTYPE);

// initialize the buzzer pin
int buzzer = 10;

// initialize the RGB LED pins
int redPin = 11;
int greenPin = 12;
int bluePin = 13;

void setup() {
  // initialize the LCD
  lcd.begin(16, 2);
  lcd.print("Air Pollution");
  lcd.setCursor(0, 1);
  lcd.print("Detection System");

  // initialize the DHT sensor
  dht.begin();

  // initialize the buzzer pin
  pinMode(buzzer, OUTPUT);

  // initialize the RGB LED pins
  pinMode(redPin, OUTPUT);
  pinMode(greenPin, OUTPUT);
  pinMode(bluePin, OUTPUT);
}

void loop() {
  // read the DHT sensor values
  float temperature = dht.readTemperature();
  float humidity = dht.readHumidity();

  // read the MQ gas sensor value
  int gasValue = analogRead(A0);

  // convert the gas value to parts per million (ppm)
  float ppm = (gasValue / 1024.0) * 10.0;

  // display the temperature, humidity, and gas value on the LCD
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("T:");
  lcd.print(temperature);
  lcd.print("C H:");
  lcd.print(humidity);
  lcd.print("%");
  lcd.setCursor(0, 1);
  lcd.print("Gas:");
  lcd.print(ppm);
  lcd.print("ppm");

  // check if the gas value exceeds the threshold
  if (ppm >= 1.0) {
    digitalWrite(buzzer, HIGH);
    lcd.setCursor(0, 1);
    lcd.print("DANGER");
    analogWrite(redPin, 255);
    analogWrite(greenPin, 0);
    analogWrite(bluePin, 0);
  }
  else if (ppm <= 0.5) {
digitalWrite(buzzer, LOW);
lcd.setCursor(0, 1);
lcd.print("FRESH AIR");
analogWrite(redPin, 0);
analogWrite(greenPin, 255);
analogWrite(bluePin, 0);
}
else {
digitalWrite(buzzer, LOW);
lcd.setCursor(0, 1);
lcd.print("MODERATE AIR");
analogWrite(redPin, 0);
analogWrite(greenPin, 0);
analogWrite(bluePin, 255);
}

// wait for a moment before reading the sensors again
delay(1000);
}
