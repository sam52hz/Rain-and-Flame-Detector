#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>

#define SCREEN_WIDTH 128
#define SCREEN_HEIGHT 64
Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, -1);

int rainPin = 2;
int flamePin = 6;
int buzzerPin = 3;
int redLed = 4;

// time set up
int alertTime = 5000;   // milliseconds (3000 = 3 sec)

void setup() {
  pinMode(rainPin, INPUT);
  pinMode(flamePin, INPUT);
  pinMode(buzzerPin, OUTPUT);
  pinMode(redLed, OUTPUT);

  Serial.begin(9600);

  if (!display.begin(SSD1306_SWITCHCAPVCC, 0x3C)) {
    Serial.println("OLED not found");
    while (1);
  }

  display.clearDisplay();
  display.setTextSize(1);
  display.setTextColor(SSD1306_WHITE);
  display.setCursor(0, 0);
  display.println("Rain + Fire");
  display.println("System Ready");
  display.display();
  delay(2000);
}

void loop() {
  int rainData = digitalRead(rainPin);
  int flameData = digitalRead(flamePin);

  display.clearDisplay();
  display.setCursor(0, 0);

  Serial.print("Rain: ");
  Serial.print(rainData);
  Serial.print("  Flame: ");
  Serial.println(flameData);

  // 🔥 FIRE DETECTED
  if (flameData == LOW) {
    digitalWrite(buzzerPin, HIGH);
    digitalWrite(redLed, HIGH);

    display.println("FIRE DETECTED");
    display.println("ALERT !!!");
    display.display();

    delay(alertTime);          // ⏱ TIME CONTROL
    digitalWrite(buzzerPin, LOW);
    digitalWrite(redLed, LOW);
  }

  // 🌧 RAIN DETECTED
  else if (rainData == LOW) {
    digitalWrite(buzzerPin, HIGH);
    digitalWrite(redLed, HIGH);

    display.println("RAIN DETECTED");
    display.println("ALERT !!!");
    display.display();

    delay(alertTime);          // ⏱ TIME CONTROL
    digitalWrite(buzzerPin, LOW);
    digitalWrite(redLed, LOW);
  }

  // ✅ NORMAL
  else {
    digitalWrite(buzzerPin, LOW);
    digitalWrite(redLed, LOW);

    display.println("STATUS: NORMAL");
    display.println("NO RAIN / NO FIRE");
    display.display();
  }

  delay(1000);
}
