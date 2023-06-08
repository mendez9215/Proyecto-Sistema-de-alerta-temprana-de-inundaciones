#include <WiFi.h>
#include <PubSubClient.h>
#include <Ultrasonic.h>
#include <DHT.h>

#define DHTPIN 14        // Pin de conexión del sensor DHT11 (GPIO4)
#define DHTTYPE DHT11   // Tipo de sensor DHT11
DHT dht(DHTPIN, DHTTYPE);

#define TRIGGER_PIN 12
#define ECHO_PIN 13
#define BUZZER 23
Ultrasonic ultrasonic(TRIGGER_PIN, ECHO_PIN);

const char* ssid = "nombre_de_la_red";
const char* password = "clave_de_la_red";
const char* mqtt_server = "broker";

WiFiClient espClient;
PubSubClient client(espClient);

float temperatura = 0.0;
float humedad = 0.0;
float distancia = 0.0;
char msg1[20];

void setup() {
  // put your setup code here, to run once:
  Serial.begin(115200);
  dht.begin();
  pinMode(BUZZER,OUTPUT);
  setup_wifi();
  client.setServer(mqtt_server,1883);
  client.setCallback(callback);
}

void loop() {
  if(!client.connected()){reconnect();}
  client.loop();
  temperatura = temp();
  humedad = hum();
  distancia = ultrasonido();
  snprintf(msg1,20,"%.2f,%.2f,%.2f",temperatura,humedad,distancia);
  client.publish("canal",msg1);
  delay(1000);
}

void reconnect(){
  if(client.connect("ESP32")){
    Serial.println(".......Conexión exitosa");
  }
}

void setup_wifi(){

  //Serial.begin(115200);
  WiFi.begin(ssid,password); //se habilitará el modo estación

  // Mientras el ESP32 no se conecte al AP:
  while(WiFi.status() != WL_CONNECTED){
    delay(200);
    Serial.print(".");
  }
  
  //Serial.println(WiFi.localIP()); //Imprimo el IP del esp32
}

void callback(char* topic, byte* payload, unsigned int length){

  payload[length]='\0';
  String val = String((char*)payload);

}

float temp() {
  float temperatura = dht.readTemperature(); // Leer la temperatura en grados Celsius
  Serial.print("Temperatura: ");
  Serial.print(temperatura);
  Serial.println(" °C");
  return temperatura;
}

float hum() {
  float humedad = dht.readHumidity(); // Leer la humedad relativa
  Serial.print(" Humedad: ");
  Serial.print(humedad);
  Serial.println(" %");
  return humedad;
}

float ultrasonido() {
  float distancia = ultrasonic.read();
  distancia = 25 - distancia;
  if (distancia > 15){digitalWrite(BUZZER, HIGH);}
  else {digitalWrite(BUZZER, LOW);}
  Serial.print("Distancia: ");
  Serial.print(distancia);
  Serial.println(" cm");
  return distancia;
}
