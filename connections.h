#include <WiFi.h>
#include <FirebaseESP32.h>
#include <addons/TokenHelper.h>
#include <addons/RTDBHelper.h>

/* Define the WiFi credentials */
#define WIFI_SSID "La Taberna de Moe"
#define WIFI_PASS "12288601"
#define LED 2

/* Define the Firebase credentials */
#define API_KEY "IXaQUWhRoZ0C2JZl7htecdDhIu8Z6En3nSI29Oad"
#define DATABASE_URL "https://smartpot-f8f23-default-rtdb.firebaseio.com/"
// Define Firebase Data object
FirebaseData fbdo;

String urlSettingData = "/smartpot_v00/setting/";
String urlTypePlantData = "/smartpot_v00/plantTypes/";
String urlSensorValues = "/smartpot_v00/sensorValues/";

int maxTemperature, minTemperature, maxSoilMoisture, minSoilMoisture;

void tryConnectToWifi() {
  WiFi.begin(WIFI_SSID, WIFI_PASS);        //Connect to WPA/WPA2 network.
  while(WiFi.status() != WL_CONNECTED) {
    delay(500);    
    Serial.println("Connecting WiFi...");
  }
  Serial.println("Connected to WiFi:");
  Serial.println(WIFI_SSID);
  Serial.println(WiFi.localIP());
  //digitalWrite(LED, HIGH);
}

void tryConnectToFirebse() {
  Serial.printf("Firebase Client v%s\n\n", FIREBASE_CLIENT_VERSION);

  Firebase.begin(DATABASE_URL, API_KEY);
  // Comment or pass false value when WiFi reconnection will control by your code or third party library
  Firebase.reconnectWiFi(true);
  Firebase.setDoubleDigits(2);

  if (Firebase.ready()) {
    Serial.print("Connection established with firebase!");
  }
}

void getPlantConfigurationData() {
  Firebase.getString(fbdo, urlSettingData + "typePlant");
  String typePlant = fbdo.stringData();

  Firebase.getInt(fbdo, urlTypePlantData + typePlant + "/maxTemperature");
  maxTemperature = fbdo.intData();
  Firebase.getInt(fbdo, urlTypePlantData + typePlant + "/minTemperature");
  minTemperature = fbdo.intData();
  Firebase.getInt(fbdo, urlTypePlantData + typePlant + "/maxSoilMoisture");
  maxSoilMoisture= fbdo.intData();
  Firebase.getInt(fbdo, urlTypePlantData + typePlant + "/minSoilMoisture");
  minSoilMoisture = fbdo.intData();

  Serial.println(maxTemperature);
  Serial.println(minTemperature);
  Serial.println(maxSoilMoisture);
  Serial.println(minSoilMoisture);
}

void isItConfigurationModified() {
  Firebase.getInt(fbdo, urlSettingData + "/modified");
  int isItModified = fbdo.intData();

  // Serial.println(isItModified);

  if(isItModified == 1) {
    getPlantConfigurationData();
    Firebase.setInt(fbdo, urlSettingData + "/modified", 0);
    // Serial.println("Modified!");
  }
  else {
    Serial.println("No Modifications");
  }
}

void setSensorValues(float temperature, int soilMoisture, int light) {
  Firebase.setDouble(fbdo, urlSensorValues + "temperature", temperature);
  Firebase.setInt(fbdo, urlSensorValues + "soilMoisture", soilMoisture);
  Firebase.setInt(fbdo, urlSensorValues + "light", light);
}