#include <LiquidCrystal_I2C.h>

#include <LiquidCrystal.h>
#include <DHT.h>


// initialize the LCD library
LiquidCrystal_I2C lcd(0x27,16,2);
//LiquidCrystal lcd(4, 5, 6, 7, 8, 9);

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
  
  Serial.begin(9600);
  // initialize the LCD
  lcd.init();
  lcd.backlight();
  lcd.begin(16, 2);
  lcd.print("Air Pollution");
  lcd.setCursor(0, 1);
  lcd.print("Detection System");
delay(100);
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
  Serial.print("Gas :");
  
  

  // convert the gas value to parts per million (ppm)
  float ppm = (gasValue / 950.0 );
  Serial.println(ppm);
  float tem = (gasValue / 20.0);
  Serial.println(tem);
  float hum = (gasValue / 22.0);
  Serial.println(hum);
  // display the temperature, humidity, and gas value on the LCD
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("Gas: ");
  lcd.print(ppm);
  lcd.print("ppm");
  
  lcd.setCursor(0, 1);

  // check if the gas value exceeds the threshold
  if (ppm >= 1.0) {
    digitalWrite(buzzer, HIGH);
    lcd.setCursor(0, 1);
    lcd.print("DANGER!!! OPEN WINDOWS");
    digitalWrite(redPin, HIGH);
    digitalWrite(greenPin, LOW);
    digitalWrite(bluePin, LOW);
  }
  else if (ppm <= 0.5) {
 digitalWrite(buzzer, LOW);
 lcd.setCursor(0, 1);
 lcd.print("FRESH AIR");
 digitalWrite(redPin, LOW);
 digitalWrite(greenPin, HIGH);
 digitalWrite(bluePin, LOW);
}
else {
digitalWrite(buzzer, LOW);
lcd.setCursor(0, 1);
lcd.print("MODERATE AIR");
digitalWrite(redPin, LOW);
digitalWrite(greenPin, LOW);
digitalWrite(bluePin, HIGH);
}

// wait for a moment before reading the sensors again
delay(1000);
}
