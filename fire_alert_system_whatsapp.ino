
#include <Wire.h>
#include <LiquidCrystal_I2C.h>
#include <WiFi.h>
#include <HTTPClient.h>
#include <UrlEncode.h>

// --- Pin Definitions ---
#define BUTTON_PIN  14
#define BUZZER_PIN  18
#define LED_PIN     4
#define FLAME_PIN   15
#define TEMP_PIN    34

// --- WiFi Credentials ---
const char* ssid = "XXXX";
const char* password = "XXX";

// --- CallMeBot WhatsApp API ---
String phoneNumber = "XXXXX";
String apiKey = "XXXXX";

// --- State ---
bool messageSent = false;

// --- LCD ---
LiquidCrystal_I2C lcd(0x27, 16, 2);

// --- Function to Send WhatsApp Alert ---
void sendWAMessage(String message) {
  String url = "https://api.callmebot.com/whatsapp.php?phone=" + phoneNumber + "&apikey=" + apiKey + "&text=" + urlEncode(message);
  HTTPClient http;
  http.begin(url);
  http.addHeader("Content-Type", "application/x-www-form-urlencoded");

  int responseCode = http.POST(url);
  if (responseCode == 200) {
    Serial.println("✅ WhatsApp message sent successfully");
  } else {
    Serial.print("❌ Error sending message. HTTP response code: ");
    Serial.println(responseCode);
  }

  http.end();
}

void setup() {
  Serial.begin(9600);
  WiFi.begin(ssid, password);
  Serial.print("Connecting to WiFi");

  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  Serial.println("\n✅ Connected to WiFi: " + WiFi.localIP().toString());

  // Initialize Pins
  pinMode(BUTTON_PIN, INPUT);
  pinMode(BUZZER_PIN, OUTPUT);
  pinMode(LED_PIN, OUTPUT);
  pinMode(FLAME_PIN, INPUT);
  pinMode(TEMP_PIN, INPUT);

  // LCD Setup
  lcd.init();
  lcd.backlight();
  lcd.setCursor(0, 0); lcd.print("Temp: ");
  lcd.setCursor(0, 1); lcd.print("Flame: ");
}

void loop() {
  // --- Temperature Reading ---
  int rawValue = analogRead(TEMP_PIN);
  float voltage = rawValue * (3.3 / 4095.0);
  float temperatureC = voltage * 100.0;

  lcd.setCursor(6, 0); lcd.print("       ");
  lcd.setCursor(6, 0); lcd.print(temperatureC, 1); lcd.print(" C");
  Serial.print("Temperature: "); Serial.print(temperatureC); Serial.println(" C");

  // --- Flame Detection ---
  int flameStatus = digitalRead(FLAME_PIN);

  if (flameStatus == HIGH) {
    lcd.setCursor(7, 1); lcd.print("No Flame ");
    Serial.println("Flame: No Flame");
    messageSent = false; // reset message state
  } else {
    lcd.setCursor(7, 1); lcd.print("Detected");
    Serial.println("Flame: Detected");

    if (!messageSent) {
      digitalWrite(LED_PIN, HIGH);
      digitalWrite(BUZZER_PIN, HIGH);
      sendWAMessage("🔥 Fire Detected! Take action immediately.");
      messageSent = true;
    }

    // Wait for button press to acknowledge
    while (digitalRead(BUTTON_PIN) == LOW) {
      delay(50); // debounce
    }

    digitalWrite(LED_PIN, LOW);
    digitalWrite(BUZZER_PIN, LOW);
  }

  delay(500);
}
