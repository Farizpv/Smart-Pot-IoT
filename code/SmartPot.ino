#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>
#include <ESP8266WiFi.h>
#define BLYNK_TEMPLATE_ID "TMPL40l8MpVIb"
#define BLYNK_TEMPLATE_NAME "Smart Pot"
#include <BlynkSimpleEsp8266.h>

#define OLED_WIDTH 128
#define OLED_HEIGHT 64
#define OLED_ADDR 0x3C

Adafruit_SSD1306 display(OLED_WIDTH, OLED_HEIGHT, &Wire, -1);

const int moisturePin = A0;
const int relayPin = D5;

char auth[] = "asDRIDQY8DgI_YA2EKpiJ2HZxa79l658";
char ssid[] = "TP-LINK_61B9";
char pass[] = "16786653";

const unsigned long wateringDelay = 10UL * 60UL * 1000UL; //10 minutes
unsigned long lastWatered=0;


void setup() {
  Serial.begin(115200);
  pinMode(relayPin, OUTPUT);
  Blynk.begin(auth, ssid, pass);

  Serial.print("Restored lastWatered: ");
  Serial.println(lastWatered);

  if (!display.begin(SSD1306_SWITCHCAPVCC, OLED_ADDR)) {
    Serial.println(F("OLED failed"));
    while (true);
  }

  display.clearDisplay();
  display.setTextSize(2);
  display.setTextColor(WHITE);
  display.setCursor(0, 0);
  display.println("Smart Pot");
  display.setCursor(0, 30);
  display.println("Starting..");
  display.display();
  delay(3000);
}
//Manual pump control via mobile
BLYNK_WRITE(V2) {
  int val = param.asInt();
  if (val == 1) {
    digitalWrite(relayPin, HIGH);
    Blynk.virtualWrite(V1, "Manual watering...");
    display.clearDisplay();
    display.setTextSize(2);
    display.setCursor(0, 0);
    display.println("Manual Water");
    display.setCursor(0, 40);
    display.println("For 7 sec");
    display.display();
    delay(7000);
    digitalWrite(relayPin, LOW);
    Blynk.virtualWrite(V1, "Pump stopped");
    Blynk.virtualWrite(V2, 0); 
    Blynk.logEvent("pump_started", "Manual Watering for 7 seconds..");
  }
}

void loop() {
  Blynk.run();
  int rawValue = analogRead(moisturePin);
  int moisturePercent = map(rawValue, 646, 301, 0, 100);
  moisturePercent = constrain(moisturePercent, 0, 100);

  Serial.print("Raw: ");
  Serial.print(rawValue);
  Serial.print(" | Moisture: ");
  Serial.print(moisturePercent);
  Serial.println("%");

  Blynk.virtualWrite(V0, moisturePercent);  

  display.clearDisplay();
  display.setTextSize(2);
  display.setCursor(0, 0);
  display.println("Soil Moisture:");
  display.setCursor(0, 40);
  display.print(moisturePercent);
  display.println("%");
  display.display();
  delay(3000);

  unsigned long currentTime = millis();

  if (moisturePercent < 40 && (lastWatered == 0 || (currentTime - lastWatered) >= wateringDelay)) {
    digitalWrite(relayPin, HIGH);
    display.clearDisplay();
    display.setTextSize(2);
    display.setCursor(0, 0);
    display.println("Status:");
    display.setCursor(0, 30);
    display.println("Watering..");
    display.display();

    Blynk.virtualWrite(V1, "Auto Watering 7 sec...");
    
    delay(7000);
    digitalWrite(relayPin, LOW);
    lastWatered = currentTime;

    display.clearDisplay();
    display.setTextSize(2);
    display.setCursor(0, 0);
    display.println("Watered!");
    display.setCursor(0, 30);
    display.println("Waiting..");
    display.display();
    Blynk.virtualWrite(V1, "Watered. Waiting 10 min...");
    Blynk.logEvent("auto_water", "Completed Auto Watering for 7 seconds.");
    delay(4000);

  } else if (moisturePercent < 40) {
    unsigned long timeLeft = wateringDelay - (currentTime - lastWatered);
    int minsLeft = timeLeft / 60000;
    int secsLeft = (timeLeft % 60000) / 1000;

    display.clearDisplay();
    display.setTextSize(2);
    display.setCursor(0, 0);
    display.print("Next in");
    display.setCursor(0, 25);
    display.print(minsLeft);
    display.print("M ");
    display.print(secsLeft);
    display.println("S");
    display.display();
    Blynk.virtualWrite(V1, "Moisture low – pump in cooldown: " + String(minsLeft) + "m " + String(secsLeft) + "s");
    delay(5000);

  } else {
    digitalWrite(relayPin, LOW);
    display.clearDisplay();
    display.setTextSize(2);
    display.setCursor(0, 0);
    display.println("Status:");
    display.setCursor(0, 30);
    display.println("Wet soil");
    display.display();
    Blynk.virtualWrite(V1, "Soil is wet. No watering needed.");
    delay(2000);
  }
}
