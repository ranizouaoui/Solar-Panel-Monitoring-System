/*
   Project: PV Data to HiveMQ
   Author: Rani Zouaoui
   Description: This program sends solar panel data to HiveMQ.
   Required Hardware:
     - Arduino board (ESP32 compatible for WiFi connection)
     - Solar panel sensor (ACS712-20A, voltage divider, LDR)
     - Internet connection (WiFi)
     - MQTT server (HiveMQ)
   Used Libraries:
     - WiFi.h: for WiFi connection management
     - PubSubClient.h: for MQTT communication
*/


#include<stdio.h>
#include <Arduino.h>
#include<string.h>
#include "esp_err.h"
#include "driver/adc.h"
#include <WiFi.h>  
#include <PubSubClient.h>
#include <WiFiClientSecure.h>
#include "DHT.h"
#define DHTPIN 4
#define DHTTYPE DHT11
DHT dht(DHTPIN, DHTTYPE);
#define MSG_BUFFER_SIZE  (50)
#define DAC1 25 // Will be connected to the MOSFET

// Pins :
int currentpin = 35;
int voltagepin = 34;
int ldrpin = 32;

//---- WiFi settings
const char* ssid = "Redmi";
const char* password = "raniphone1234";

//---- MQTT Broker settings
const char* mqtt_server = "fab112e11000421b9ad44cc238fe2452.s2.eu.hivemq.cloud"; // replace with your broker url
const char* mqtt_username = "ranizouaoui";
const char* mqtt_password = "Rani123@";
const int mqtt_port =8883;
WiFiClientSecure espClient;   // for no secure connection use WiFiClient instead of WiFiClientSecure 
//WiFiClient espClient;
PubSubClient client(espClient);
unsigned long lastMsg = 0;
HardwareSerial SerialPort(2); // use UART2
float newmumber;
char msg[MSG_BUFFER_SIZE];

// initialization of variables
float voltage = 0;
float voltage_0 = 0;
float current = 0;
float ldr = 0;
float power = 0;

int command1 =0;

// the resistors associated with the divider bridge
float R1 = 2000.0;
float R2 = 1000.0;
// the resistors associated with the divider bridge of the acs712
float R3 = 400.0; // r1
float R4 = 400.0; // r2

const char* sensor1_topic= "voltage";
const char*  sensor2_topic="current";
const char*  sensor3_topic="ldr";
const char*  sensor4_topic="power";
const char*  sensor5_topic="humidity";
const char*  sensor6_topic="temperature";
const char* command1_topic="command1";
static const char *root_ca PROGMEM = R"EOF(
-----BEGIN CERTIFICATE-----
MIIFazCCA1OgAwIBAgIRAIIQz7DSQONZRGPgu2OCiwAwDQYJKoZIhvcNAQELBQAw
TzELMAkGA1UEBhMCVVMxKTAnBgNVBAoTIEludGVybmV0IFNlY3VyaXR5IFJlc2Vh
cmNoIEdyb3VwMRUwEwYDVQQDEwxJU1JHIFJvb3QgWDEwHhcNMTUwNjA0MTEwNDM4
WhcNMzUwNjA0MTEwNDM4WjBPMQswCQYDVQQGEwJVUzEpMCcGA1UEChMgSW50ZXJu
ZXQgU2VjdXJpdHkgUmVzZWFyY2ggR3JvdXAxFTATBgNVBAMTDElTUkcgUm9vdCBY
MTCCAiIwDQYJKoZIhvcNAQEBBQADggIPADCCAgoCggIBAK3oJHP0FDfzm54rVygc
h77ct984kIxuPOZXoHj3dcKi/vVqbvYATyjb3miGbESTtrFj/RQSa78f0uoxmyF+
0TM8ukj13Xnfs7j/EvEhmkvBioZxaUpmZmyPfjxwv60pIgbz5MDmgK7iS4+3mX6U
A5/TR5d8mUgjU+g4rk8Kb4Mu0UlXjIB0ttov0DiNewNwIRt18jA8+o+u3dpjq+sW
T8KOEUt+zwvo/7V3LvSye0rgTBIlDHCNAymg4VMk7BPZ7hm/ELNKjD+Jo2FR3qyH
B5T0Y3HsLuJvW5iB4YlcNHlsdu87kGJ55tukmi8mxdAQ4Q7e2RCOFvu396j3x+UC
B5iPNgiV5+I3lg02dZ77DnKxHZu8A/lJBdiB3QW0KtZB6awBdpUKD9jf1b0SHzUv
KBds0pjBqAlkd25HN7rOrFleaJ1/ctaJxQZBKT5ZPt0m9STJEadao0xAH0ahmbWn
OlFuhjuefXKnEgV4We0+UXgVCwOPjdAvBbI+e0ocS3MFEvzG6uBQE3xDk3SzynTn
jh8BCNAw1FtxNrQHusEwMFxIt4I7mKZ9YIqioymCzLq9gwQbooMDQaHWBfEbwrbw
qHyGO0aoSCqI3Haadr8faqU9GY/rOPNk3sgrDQoo//fb4hVC1CLQJ13hef4Y53CI
rU7m2Ys6xt0nUW7/vGT1M0NPAgMBAAGjQjBAMA4GA1UdDwEB/wQEAwIBBjAPBgNV
HRMBAf8EBTADAQH/MB0GA1UdDgQWBBR5tFnme7bl5AFzgAiIyBpY9umbbjANBgkq
hkiG9w0BAQsFAAOCAgEAVR9YqbyyqFDQDLHYGmkgJykIrGF1XIpu+ILlaS/V9lZL
ubhzEFnTIZd+50xx+7LSYK05qAvqFyFWhfFQDlnrzuBZ6brJFe+GnY+EgPbk6ZGQ
3BebYhtF8GaV0nxvwuo77x/Py9auJ/GpsMiu/X1+mvoiBOv/2X/qkSsisRcOj/KK
NFtY2PwByVS5uCbMiogziUwthDyC3+6WVwW6LLv3xLfHTjuCvjHIInNzktHCgKQ5
ORAzI4JMPJ+GslWYHb4phowim57iaztXOoJwTdwJx4nLCgdNbOhdjsnvzqvHu7Ur
TkXWStAmzOVyyghqpZXjFaH3pO3JLF+l+/+sKAIuvtd7u+Nxe5AW0wdeRlN8NwdC
jNPElpzVmbUq4JUagEiuTDkHzsxHpFKVK7q4+63SM1N95R1NbdWhscdCb+ZAJzVc
oyi3B43njTOQ5yOf+1CceWxG1bQVs5ZufpsMljq4Ui0/1lvh+wjChP4kqKOJ2qxq
4RgqsahDYVvTH9w7jXbyLeiNdd8XM2w9U/t7y0Ff/9yi0GE44Za4rF2LN9d11TPA
mRGunUHBcnWEvgJBQl9nJEiU0Zsnvgc/ubhPgXRR4Xq37Z0j4r7g1SgEEzwxA57d
emyPxgcYxn/eR44/KJ4EBs+lVDR3veyJm+kXQ99b21/+jh5Xos1AnX5iItreGCc=
-----END CERTIFICATE-----
)EOF";
void setup_wifi() {
  delay(10);
  Serial.print("\nConnecting to ");
  Serial.println(ssid);

  WiFi.mode(WIFI_STA);
  WiFi.begin(ssid, password);

  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  randomSeed(micros());
  Serial.println("\nWiFi connected\nIP address: ");
  Serial.println(WiFi.localIP());
}
void reconnect() {
  // Loop until we're reconnected
  while (!client.connected()) {
    Serial.print("Attempting MQTT connection...");
    String clientId = "ESP8266Client-";   // Create a random client ID
    clientId += String(random(0xffff), HEX);
    // Attempt to connect
    if (client.connect(clientId.c_str(), mqtt_username, mqtt_password)) {
      Serial.println("connected");

      client.subscribe(command1_topic);   // subscribe the topics here
    } else {
      Serial.print("failed, rc=");
      Serial.print(client.state());
      Serial.println(" try again in 5 seconds");   // Wait 5 seconds before retrying
      delay(5000);
    }
  }
}
void callback(char* topic, byte* payload, unsigned int length) {
  String incommingMessage = "";
  for (int i = 0; i < length; i++) incommingMessage+=(char)payload[i];
  
  Serial.println("Message arrived ["+String(topic)+"]"+incommingMessage);
  
  //--- check the incomming message


   //  check for other commands
 /*  else  if( strcmp(topic,command2_topic) == 0){
     if (incommingMessage.equals("1")) {  } // do something else
  }
  */
}
void publishMessage(const char* topic, String payload , boolean retained){
  if (client.publish(topic, payload.c_str(), true))
      Serial.println("Message publised ["+String(topic)+"]: "+payload);
}
void setup()
{
  Serial.begin(115200);
  dht.begin();
  SerialPort.begin(115200, SERIAL_8N1, 16, 17);
  pinMode(currentpin, INPUT);
  pinMode(voltagepin, INPUT);
  pinMode(ldrpin, INPUT);
 Serial.print("Voltage");
Serial.print("\t  ");
Serial.print("Current");
Serial.print("\t  ");
Serial.print("Power");
Serial.print("\t  ");
Serial.print("LDR");
    Serial.print("\t  ");
    Serial.print("   ");
    Serial.print("temp");
    Serial.print("\t  ");
    Serial.print("   ");
    Serial.println("hum");
  while (!Serial){delay(1);}
  setup_wifi();
  espClient.setCACert(root_ca);      // enable this line and the the "certificate" code for secure connection.
  client.setServer(mqtt_server, mqtt_port);
  client.setCallback(callback);
}
void loop()
{
if (!client.connected()){
  reconnect();
  } 
  client.loop();  
        int Value = 255;
        dacWrite(DAC1, Value);
        //PV panel voltage
        voltage_0 = (analogRead(voltagepin)*3.3/4095);     
        voltage = (voltage_0*(R1 + R2)/R2);
        //PV panel current with acs712-20A;
//        int adc = analogRead(currentpin);
//        float adc_voltage = adc * (3.3 / 4096.0);
//        float current_voltage = (adc_voltage * (R3+R4)/R4);
//         current = ((current_voltage - 2.5) / 0.185)* (R3+R4)/R4;
        // LDR
         current = (analogRead(currentpin)*3.3/4095); 
        ldr = analogRead(ldrpin);
        power = voltage*current;
        float humidity = dht.readHumidity();
        // Read temperature as Celsius (the default)
        float temperature = dht.readTemperature();
        publishMessage(sensor1_topic,String(voltage),true);
        publishMessage(sensor2_topic,String(current),true);
        publishMessage(sensor3_topic,String(ldr),true);
        publishMessage(sensor4_topic,String(power),true);
        publishMessage(sensor5_topic,String(temperature),true);
        publishMessage(sensor6_topic,String(humidity),true);

//    Serial.print(voltage,3);    //send the voltage to serial port
//    Serial.print("\t  ");
//    Serial.print("  ");
//    Serial.print(current,3);    //send the current to serial port
//    Serial.print("\t  ");
//    Serial.print("  ");
//    Serial.print(power);
//    Serial.print("\t  ");
//    Serial.print("   ");
//    Serial.print(ldr);
//    Serial.print("\t  ");
//    Serial.print("   ");
//    Serial.print(t);
//    Serial.print("\t  ");
//    Serial.print("   ");
//    Serial.println(h);

  delay(2000);
 }
       
