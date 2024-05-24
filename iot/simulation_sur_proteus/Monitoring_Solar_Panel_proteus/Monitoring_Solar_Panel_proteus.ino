//--------------------------------
// I-V-P for Solar pannel 2024 - Rani zouaoui
//-------------------------------
#include <Wire.h>           //wire library
#include <DHT.h>

// DHT11 Variables :
#define DHTPIN A0 // sensor is connected to Analog Pin
#define DHTTYPE DHT11   // DHT 11
DHT dht(DHTPIN, DHTTYPE);
// ACS Variables :
const int nSamples = 1000;
const float vcc = 5.0;
const int adcMax = 1023;
const float sens = 0.100;  // 20A
float avg() {
  float val = 0;
  for (int i = 0; i < nSamples; i++) {
    val += analogRead(A1);
    delay(1);
  }
  return val / adcMax / nSamples;
}
void setup() {
dht.begin();
//opens serial port, sets data rate to 9600 bps
Serial.begin(9600);
Serial.print("Voltage");
Serial.print("\t  ");
Serial.print("Current");
Serial.print("\t  ");
Serial.print("Power");
Serial.print("\t  ");
Serial.print("temperature");
Serial.print("\t  ");
Serial.print("LDR");
Serial.print("\t  ");
Serial.println("humidity");
pinMode(2, OUTPUT);
}

void loop() {
    digitalWrite(2, HIGH); 
    float current = (vcc / 2 - vcc * avg()) / sens;
    float voltage = (analogRead(A2)*5.0/1023)*3; 
    float power = voltage*current;
    float temperature = dht.readTemperature();
    float humidity = dht.readHumidity();
    int   ldr = analogRead(A3);
    Serial.print(voltage,3);    //send the voltage to serial port
    Serial.print("\t  ");
    Serial.print("  ");
    Serial.print(current,3);    //send the current to serial port
    Serial.print("\t  ");
    Serial.print("  ");
    Serial.print(power);
    Serial.print("\t  ");
    Serial.print("   ");
    Serial.print(temperature);
    Serial.print("\t  ");
    Serial.print("   ");
    Serial.print(ldr);
    Serial.print("\t  ");
    Serial.print("   ");
    Serial.println(humidity);
    delay(250); 
}
