#include <ESP8266WiFi.h>
#include <DHT.h>

#define DHTPIN 5
#define DHTTYPE DHT11 // Tipo de sensor DHT11

DHT dht(DHTPIN, DHTTYPE);
const char* ssid     = "AuxSmartLab";
const char* password = "poli1234";

WiFiServer server(80);

void setup()
{
    Serial.begin(115200);
    dht.begin();     // configuro el pin del LED

    delay(10);  

    // We start by connecting to a WiFi network

    Serial.println();
    Serial.println();
    Serial.print("Conectando a ");
    Serial.println(ssid);

    WiFi.begin(ssid, password);

    while (WiFi.status() != WL_CONNECTED) {
        delay(500);
        Serial.print(".");
    }

    Serial.println("");
    Serial.println("WiFi conectado.");
    Serial.println("direccion IP: ");
    Serial.println(WiFi.localIP());
    
    server.begin();

}

int value = 0;

void loop(){
 WiFiClient client = server.available();   // listen for incoming clients
 float temperature = dht.readTemperature();
 float humidity = dht.readHumidity();

  // Mostrar los valores en el monitor serial

  if (client) {                             // if you get a client,
    Serial.println("New Client.");           // print a message out the serial port
    String currentLine = "";                // make a String to hold incoming data from the client
    while (client.connected()) {            // loop while the client's connected
      if (client.available()) {             // if there's bytes to read from the client,
        char c = client.read();             // read a byte, then
        Serial.write(c);                    // print it out the serial monitor
        if (c == '\n') {                    // if the byte is a newline character

          // if the current line is blank, you got two newline characters in a row.
          // that's the end of the client HTTP request, so send a response:
          if (currentLine.length() == 0) {
            // HTTP headers always start with a response code (e.g. HTTP/1.1 200 OK)
            // and a content-type so the client knows what's coming, then a blank line:
            client.println("HTTP/1.1 200 OK");
            client.println("Content-type:text/html");
            client.println();
            client.print("Temperatura: ");
            client.print(temperature);
            client.print("Humedad: ");
            client.print(humidity);
            // the content of the HTTP response follows the header:
            //while(temperature != NULL && humidity != NULL){
              
             // Serial.print("Temperatura: ");
             // Serial.print(temperature);
             // Serial.print(" °C\t");
             // Serial.print("Humedad: ");
             // Serial.print(humidity);
             // Serial.println(" %");
            //}
            // The HTTP response ends with another blank line:
            client.println();
            // break out of the while loop:
            break;
          } else {    // if you got a newline, then clear currentLine:
            currentLine = "";
          }
        } else if (c != '\r') {  // if you got anything else but a carriage return character,
          currentLine += c;      // add it to the end of the currentLine
        }

        // Check to see if the client request was "GET /H" or "GET /L":
       
      }
    }
    // close the connection:
    client.stop();
    Serial.println("Cliente Desconectado.");
  }
}