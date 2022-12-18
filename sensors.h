/* Define the LM35 Temperature Sensor variables */
#define ADC_VREF_mV    3300.0 // in millivolt
#define ADC_RESOLUTION 4096.0
#define PIN_LM35       34 // ESP32 pin GIOP34 (ADC0) connected to LM35

/* Define the Soil Moisture Sensor variables */
#define AOUT_PIN 39 // ESP32 pin GIOP36 (ADC0) that connects to AOUT pin of moisture sensor

/* Define the Light Sensor variables */
#define LIGHT_SENSOR_PIN 35 // ESP32 pin GIOP36 (ADC0)

float temperatureSensorValue() {
    // read the ADC value from the temperature sensor
    int analogValue = analogRead(PIN_LM35);
    // convert the ADC value to voltage in millivolt
    float milliVolt = analogValue * (ADC_VREF_mV / ADC_RESOLUTION);
    // convert the voltage to the temperature in °C
    float tempC = milliVolt / 10;

    return(tempC);
}

int soilMoistureSensorValue() {
    // read the analog value from sensor (value between 0 and 4095)
    int analogValue = analogRead(AOUT_PIN);
    int percentage = map(analogValue, 0, 4095, 0, 100);

    return(percentage);
}

int lightSensorValue() {
    // reads the input on analog pin (value between 0 and 4095)
    int analogValue = analogRead(LIGHT_SENSOR_PIN);
    int percentage = map(analogValue, 0, 4095, 100, 0);

    return(percentage);
}