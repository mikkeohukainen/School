// RTCZero - Version: Latest
#include <RTCZero.h>

// MAX6675 library - Version: Latest
#include <max6675.h>

//DHT-22 libraries
#include <DHT.h>
#include <DHT_U.h>

#include "thingProperties.h"

#define DHTPIN1 20
#define DHTPIN2 21

#define DHTTYPE DHT22
DHT dht1(DHTPIN1, DHTTYPE);
DHT dht2(DHTPIN2, DHTTYPE);

//  DHT22 timers
unsigned long startMillis;
unsigned long currentMillis;
const unsigned long period = 10000;

/// Reed switch variables
const int hallPins[] = {15, 16};                // Input pins
const int numSensors = 2;                       // Number of sensors
const unsigned long openDelay = 200;            // Door opening delay
bool isDoorOpen[] = {false, false};             // Door status
unsigned long hallHighStartTime[] = {0, 0};     // Timestamp of the last opening
int doorOpenCount[] = {0, 0};                   // Amount of openings
int lastHallState[] = {LOW, LOW};               // Latest status of the doors
int doorOpenTimestampsSize[] = {0, 0};          // Amount of time stamps
const int maxTimestampsPerDoor = 200;           // Max number of time stamps

// Table for the timestamps
unsigned long doorOpenTimestamps[numSensors][maxTimestampsPerDoor];
const unsigned long tarkasteluaika = 30  *  60 * 1000;

int thermoDO = 10;
int thermoCS = 11;
int thermoCLK = 12;

MAX6675 thermocouple(thermoCLK, thermoCS, thermoDO);

void setup() {

  for (int i = 0; i < numSensors; i++) {
    pinMode(hallPins[i], INPUT_PULLUP);
  }
  Serial.begin(9600);
  dht1.begin();
  dht2.begin();
  startMillis = millis();
  delay(1500);

  initProperties();

  ArduinoCloud.begin(ArduinoIoTPreferredConnection);
  setDebugMessageLevel(2);
  ArduinoCloud.printDebugInfo();
}

void loop() {
  ArduinoCloud.update();
  checkHall(0);
  checkHall(1);
  currentMillis = millis();

  ovien_avaukset_per_vrk = doorOpenCount[0] + doorOpenCount[1];


  if (currentMillis - startMillis >= period)
  {
    getOpenCountLastHour(0);
    getOpenCountLastHour(1);
    ovien_Avaustaajuus = doorOpenTimestampsSize[0] + doorOpenTimestampsSize[1];
    Serial.print("Ovien keskimääräinen avaustahti ");
    Serial.print(ovien_Avaustaajuus);
    Serial.print("kertaa ");
    Serial.print((tarkasteluaika / 1000.0) / 60, 1);
    Serial.println(" minuutin aikana.");

    palokaasut = thermocouple.readCelsius();

    delay(500);

    if (palokaasut < 0) {
      // If there is an error with the TC, temperature will be < 0
      Serial.print("Thermocouple Error on CS");
      Serial.println( palokaasut );
    }
    else {
      Serial.print("Palokaasujen lämpötila: ");
      Serial.println( palokaasut );
    }

    dHT22_humid = dht1.readHumidity();
    dHT22_temp = dht1.readTemperature();
    dHT22_temp2 = dht2.readTemperature();

    Serial.print("Humidity: ");
    Serial.print(dHT22_humid);
    Serial.println(" %");
    Serial.print("Saunan lämpötila: ");
    Serial.print(dHT22_temp);
    Serial.println(" Celsius");

    Serial.print("Ulkolämpötila: ");
    Serial.print(dHT22_temp2);
    Serial.println(" Celsius\n");
    startMillis = currentMillis;
  }

}

int getOpenCountLastHour(int door) {
  unsigned long currentTime = millis(); // Present moment
  int count = 0;                        // Counter for the timestamps

  for (int i = 0; i < doorOpenTimestampsSize[door]; i++) {              // Go through all the timestamps
    if (currentTime - doorOpenTimestamps[door][i] <= tarkasteluaika) {  // If inside 1h,
      doorOpenTimestamps[door][count++] = doorOpenTimestamps[door][i];  // move it to the next index, count++
    }
  }

  doorOpenTimestampsSize[door] = count;

  return count;
}

void openDoor(int door) {
  isDoorOpen[door] = true;
  doorOpenCount[door]++;
  doorOpenTimestamps[door][doorOpenTimestampsSize[door]++] = millis(); // Save the timestamp and increase the table size
  Serial.print(door);
  Serial.println(" on auki.\n");
  Serial.print("Ovi avattu yhteensä ");
  Serial.print(doorOpenCount[door]);
  Serial.println(" kertaa.\n");
}

void closeDoor(int door) {
  Serial.print("Ovi ");
  Serial.print(door);
  Serial.print(" suljettu.\n");
  isDoorOpen[door] = false;
}

void checkHall(int sensor) {
  int hallState = digitalRead(hallPins[sensor]);

  if (hallState == HIGH && lastHallState[sensor] == LOW) {
    hallHighStartTime[sensor] = millis();
  }

  if (hallState == HIGH && millis() - hallHighStartTime[sensor] >= openDelay && !isDoorOpen[sensor]) {
    openDoor(sensor);
  }

  if (hallState == LOW && isDoorOpen[sensor]) {
    closeDoor(sensor);
  }
  lastHallState[sensor] = hallState;
}
