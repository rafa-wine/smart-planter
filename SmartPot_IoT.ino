#include "connections.h"
#include "sensors.h"
#include "animations.h"

/* Global variables */

float temperature;
int soilMoisture, light;

/* Create concurrent tasks variable */

TaskHandle_t taskFirebase;

void setup() {
  Serial.begin(115200);

  /* Attempt to start OLED Display */
  startDisplay();

  welcomeAnimation();
  
  connectToWifi();

  /* Attempt to connect to WiFi */
  tryConnectToWifi();
  /* Attempt to connect to Firebase */
  tryConnectToFirebse();
  /* Attempt get plant configuration data */
  getPlantConfigurationData();

  /* Create concurrent tasks */
  xTaskCreatePinnedToCore(
    taskFirebaseCode,   /* Task function. */
    "taskFirebase",     /* name of task. */
    15000,             /* Stack size of task */
    NULL,              /* parameter of the task */
    0,                 /* priority of the task */
    &taskFirebase,      /* Task handle to keep track of created task */
    0);                /* pin task to core 0 */

  for(int i=0; i<6; i++) {
    sleepAnimation();
  }
  
  yawnAnimation();
}

void taskFirebaseCode (void * parameter) {
  delay(500);
  for (;;) {
    isItConfigurationModified();
    setSensorValues(temperature, soilMoisture, light);
  }
}

void loop() {
  /* get sensors values */
  temperature = temperatureSensorValue();
  soilMoisture = soilMoistureSensorValue();
  light = lightSensorValue();

  /* Display information */
  if(temperature > minTemperature && temperature < maxTemperature && soilMoisture > minSoilMoisture && soilMoisture < maxSoilMoisture)  {
    if(light > 20){
      normalAnimation();
    }
    else {
      vampireAnimation();
    }
  }
  else {
    if((temperature < minTemperature || temperature > maxTemperature) && (soilMoisture < minSoilMoisture || soilMoisture > maxSoilMoisture)) {
      sickAnimation();
    }
    else {
      if(temperature < minTemperature) {
        lowTemperatureAnimation();
      }
      else if(temperature > maxTemperature) {
        highTemperatureAnimation();
      }
      else if(soilMoisture < minSoilMoisture) {
        drySoilAnimation();
      }
      else {
        veryWetSoilAnimation();
      }
    }
  }
}
