#include <Wire.h>
#include <LiquidCrystal_I2C.h>

#define MQ135_PIN A0          // MQ-135 sensor connected to analog pin A0
#define GREEN_LED_PIN 9       // Green LED connected to digital pin 2
#define RED_LED_PIN 7         // Red LED connected to digital pin 3
#define BUZZER_PIN 8          // Buzzer connected to digital pin 4

const int AQ_THRESHOLD = 160; // Air quality threshold (adjust based on calibration)

// Initialize the LCD with I2C address 0x27, 16 chars, and 2 lines
LiquidCrystal_I2C lcd(0x27, 16, 2);

void setup() {
  pinMode(GREEN_LED_PIN, OUTPUT);
  pinMode(RED_LED_PIN, OUTPUT);
  pinMode(BUZZER_PIN, OUTPUT);
  
  lcd.begin();
  lcd.backlight();
  lcd.setCursor(0, 0);
  lcd.print("Air Quality Index");
  
  delay(2000);
}
void loop() {
  int airQuality = analogRead(MQ135_PIN); // Read MQ-135 sensor value
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("AQI: ");
  lcd.print(airQuality);

  if (airQuality > AQ_THRESHOLD) { 
    // Bad air quality
    digitalWrite(RED_LED_PIN, HIGH);      // Turn on red LED
    digitalWrite(GREEN_LED_PIN, LOW);     // Turn off green LED
    digitalWrite(BUZZER_PIN, HIGH);       // Turn on buzzer
    lcd.setCursor(0, 1);
    lcd.print("Air: Poor");
  } else { 
    // Good air quality
    digitalWrite(GREEN_LED_PIN, HIGH);    // Turn on green LED
    digitalWrite(RED_LED_PIN, LOW);       // Turn off red LED
    digitalWrite(BUZZER_PIN, LOW);        // Turn off buzzer
    lcd.setCursor(0, 1);
    lcd.print("Air: Good");
  }

  delay(1000); // Update every second
}