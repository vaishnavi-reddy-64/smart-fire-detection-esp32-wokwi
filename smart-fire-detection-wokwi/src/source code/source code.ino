#include <DHT.h>

#define DHT_PIN 4
#define DHT_TYPE DHT22

#define MQ2_PIN 34
#define FLAME_PIN 27

#define BUZZER_PIN 26
#define RELAY_PIN 25
#define FIRE_LED 2

DHT dht(DHT_PIN, DHT_TYPE);

float temperatureThreshold =50.0;
int smokeThreshold = 2000;

void setup() {

  Serial.begin(115200);

  dht.begin();

  pinMode(FLAME_PIN, INPUT);

  pinMode(BUZZER_PIN, OUTPUT);
  pinMode(RELAY_PIN, OUTPUT);
  pinMode(FIRE_LED, OUTPUT);

  // Start with all outputs OFF
  digitalWrite(BUZZER_PIN, LOW);
  digitalWrite(RELAY_PIN, LOW);
  digitalWrite(FIRE_LED, LOW);

  Serial.println("================================");
  Serial.println("SMART FIRE DETECTION SYSTEM");
  Serial.println("System Started");
  Serial.println("================================");
}

void loop() {

  // Read sensors
  float temperature = dht.readTemperature();
  int smokeValue = analogRead(MQ2_PIN);
  int flameValue = digitalRead(FLAME_PIN);

  // Check temperature sensor
  if (isnan(temperature)) {

    Serial.println("Temperature sensor error");

    digitalWrite(BUZZER_PIN, LOW);
    digitalWrite(RELAY_PIN, LOW);
    digitalWrite(FIRE_LED, LOW);

    delay(2000);
    return;
  }
// LDR-based simulated flame/light condition
  bool flameDetected = (flameValue == LOW);

  // Check thresholds
  bool highTemperature =
      temperature >= temperatureThreshold;

  bool highSmoke =
      smokeValue >= smokeThreshold;

  // Calculate risk score
  int riskScore = 0;

  if (highTemperature) {
    riskScore += 1;
  }

  if (highSmoke) {
    riskScore += 1;
  }

  if (flameDetected) {
    riskScore += 2;
  }

  // Display sensor values
  Serial.println();
  Serial.println("--------------------------------");

  Serial.print("Temperature: ");
  Serial.print(temperature);
  Serial.println(" C");

  Serial.print("Smoke Level: ");
  Serial.println(smokeValue);

  Serial.print("Simulated Flame/Light: ");

  if (flameDetected) {
    Serial.println("DETECTED");
  } else {
    Serial.println("NOT DETECTED");
  }

  Serial.print("Risk Score: ");
  Serial.println(riskScore);

  // Fire decision
  if (riskScore >= 3) {

    Serial.println("FIRE DETECTED!");

    // Local warning
    digitalWrite(BUZZER_PIN, HIGH);
    digitalWrite(FIRE_LED, HIGH);

    // Automatic response
    digitalWrite(RELAY_PIN, HIGH);

  } else {

    Serial.println("STATUS: SAFE");

    // Turn everything off
    digitalWrite(BUZZER_PIN, LOW);
    digitalWrite(FIRE_LED, LOW);
    digitalWrite(RELAY_PIN, LOW);
  }

  delay(2000);
}