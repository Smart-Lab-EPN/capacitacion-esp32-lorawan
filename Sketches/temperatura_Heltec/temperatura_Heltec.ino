#include <DHT.h>

#define DHTPIN 21     // Pin donde está conectado el sensor DHT11
#define DHTTYPE DHT11 // Tipo de sensor DHT11

DHT dht(DHTPIN, DHTTYPE);

void setup() {
  Serial.begin(9600); // Iniciar el monitor serial
  dht.begin();        // Iniciar el sensor DHT11
}

void loop() {
  // Leer la temperatura y la humedad del sensor
  float temperature = dht.readTemperature();
  float humidity = dht.readHumidity();

  // Mostrar los valores en el monitor serial
  Serial.print("Temperatura: ");
  Serial.print(temperature);
  Serial.print(" °C\t");
  Serial.print("Humedad: ");
  Serial.print(humidity);
  Serial.println(" %");

  delay(2000); // Esperar 2 segundos para tomar otra lectura
}
