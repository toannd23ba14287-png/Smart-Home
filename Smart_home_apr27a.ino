#include "arduino_secrets.h"
#include "thingProperties.h"
#include "SmartHome.h"

SmartHome myHome(5, 18, 21, 22, 23);

const long offDelay = 5000;
unsigned long lastDetectionTime = 0;
bool isLightOn = false;

// --- POWER SAVING PROTECTION LOCK ---
bool manualOff = false;

void setup() {
  Serial.begin(9600);
  delay(1500);

  initProperties();
  ArduinoCloud.begin(ArduinoIoTPreferredConnection);

  myHome.begin();

  if (detectThreshold == 0) {
    detectThreshold = 150;
  }
  Serial.println("The system is ready to connect to the Cloud!");
}

void loop() {
  ArduinoCloud.update();

  float distanceCm = myHome.readDistance();
  currentdistance = distanceCm;

  Serial.print("Distance: ");
  Serial.print(distanceCm);
  Serial.println(" cm");

// ONLY RUN IN AUTOMATIC MODE WHEN NOT LOCKED
  if (!manualOff) {
    if (distanceCm >= 2 && distanceCm <= detectThreshold) {
      lastDetectionTime = millis();

      if (!isLightOn) {
        applyColorFromCloud();
        isLightOn = true;
        Serial.println("SOMEONE'S HERE -> TURN ON THE LIGHTS!");
      }
    } else {
      if (isLightOn && (millis() - lastDetectionTime >= offDelay)) {
        myHome.turnOffLed();
        isLightOn = false;
        Serial.println("NO ONE HERE -> TURN OFF THE LIGHTS!");
      }
    }
  }

  delay(100);
}

void applyColorFromCloud() {
  uint8_t r, g, b;
  ledColor.getValue().getRGB(r, g, b);
  uint8_t brightness = ledColor.getBrightness();

  myHome.turnOnLed(r, g, b, brightness);
}

// Arduino Cloud Callback Functions

void onLedColorChange()  {
  if (ledColor.getSwitch()) {
   // DARKNESS: You command "ON" -> Unlock, restore automatic mode
    manualOff = false;
    applyColorFromCloud();
    isLightOn = true;
    lastDetectionTime = millis();
    Serial.println(">>> UNLOCKED, RETURN TO AUTOMATIC");
  } else {
    // WHEN IT'S MORNING: You give the command "OFF" -> Permanently lock the sensor.
    manualOff = true;
    myHome.turnOffLed();
    isLightOn = false;
    Serial.println(">>> SENSOR LOCKED (ENERGY SAVING)");
  }
}

void onDetectThresholdChange()  {
  Serial.print("The detection threshold has been changed to: ");
  Serial.println(detectThreshold);
}

void onCurrentdistanceChange() {
}