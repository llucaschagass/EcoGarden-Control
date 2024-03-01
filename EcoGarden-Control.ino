#include <OneWire.h>
#include <DallasTemperature.h>

#define TEMPERATURE_PIN 2
#define RELAY_FAN_PIN 4
#define RELAY_PUMP_PIN 5
#define BUTTON_PIN 3

OneWire oneWire(TEMPERATURE_PIN);
DallasTemperature sensors(&oneWire);

bool fanState = false;
bool pumpState = false;

void setup() {
  pinMode(RELAY_FAN_PIN, OUTPUT);
  pinMode(RELAY_PUMP_PIN, OUTPUT);
  pinMode(BUTTON_PIN, INPUT_PULLUP);
  sensors.begin();
  Serial.begin(9600);
}

void loop() {
  sensors.requestTemperatures();
  float temperature = sensors.getTempCByIndex(0);
  Serial.print("Temperatura: ");
  Serial.println(temperature);

  // Verifica se a temperatura está alta e liga a ventoinha
  if (temperature > 30) {
    digitalWrite(RELAY_FAN_PIN, HIGH);
    fanState = true;
  } else {
    digitalWrite(RELAY_FAN_PIN, LOW);
    fanState = false;
  }

  // Verifica se o botão foi pressionado e liga a bomba d'água
  if (digitalRead(BUTTON_PIN) == LOW) {
    digitalWrite(RELAY_PUMP_PIN, HIGH);
    pumpState = true;
  } else {
    digitalWrite(RELAY_PUMP_PIN, LOW);
    pumpState = false;
  }

  delay(1000); // Aguarda 1 segundo entre as leituras de temperatura
}
