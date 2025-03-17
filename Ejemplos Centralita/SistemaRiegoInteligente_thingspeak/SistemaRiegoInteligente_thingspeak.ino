/**
 * Servidor Web ESP32 básico con conexión con ThingSpeak.
 *
 * Se crea una interfaz web con estilo básico para visualizar datos de sensores
 * (lluvia, humedad del suelo, luz, temperatura y humedad), así como se muestran
 * gráficas en ThingSpeak con la variación de los datos captados con los sensores.
 */

#include <WiFi.h>
#include <HTTPClient.h>
#include <DHT.h>

// Configuración de WiFi
const char* ssid     = "Livebox6-C679";
const char* password = "ns3oLuK9a95s";

// Configuración del Servidor Web y del sensor DHT
WiFiServer server(80);
DHT sensorDHT(17, DHT22);

// Pines para relé y sensores analógicos
const int rele = 4;
const int sensorLluvia = 32;
const int sensorHumedadSuelo = 33;
const int sensorLuz = 34;
const int rgb_blue = 27;

// Contador de conexión WiFi y variable para el HTTP header
int contconexion = 0;
String header;

// API Key de ThingSpeak (reemplaza VYMTXLTC8LG8074J por tu "Write API key")
String apiKey = "F1KVOS3SD4AKTYRY";
//declaramos la función para clear la página web
String crearPaginaWeb(int lecturaLluvia, int lecturaHumedadSuelo, int lecturaLuz, float lecturaTemperatura, float lecturaHumedad);

void setup() {
  Serial.begin(115200);
  pinMode(sensorLluvia, INPUT);
  pinMode(sensorHumedadSuelo, INPUT);
  pinMode(sensorLuz, INPUT);
  pinMode(rele, OUTPUT);
  pinMode(rgb_blue, OUTPUT);
  digitalWrite(rele, LOW);
  digitalWrite(rgb_blue, HIGH);
  sensorDHT.begin();
  
  WiFi.begin(ssid, password);
  Serial.print("Conectando a WiFi");
  while (WiFi.status() != WL_CONNECTED && contconexion < 50) {
    contconexion++;
    delay(500);
    Serial.print(".");
  }
  if (WiFi.status() == WL_CONNECTED) {
    Serial.println("\nWiFi conectado");
    Serial.println("IP: " + WiFi.localIP().toString());
    server.begin();
  } else {
    Serial.println("\nError de conexión al WiFi");


  }
}

String crearPaginaWeb(int lecturaLluvia, int lecturaHumedadSuelo, int lecturaLuz, float lecturaTemperatura, float lecturaHumedad) {
  // Aquí va la implementación completa de la función, por ejemplo:
  String pagina = "<!DOCTYPE html><html><head><meta charset='utf-8'><title>Sistema de Riego Inteligente</title></head><body>";
  pagina += "<h1>Datos del Sistema</h1>";
  pagina += "<p>Lluvia: " + String(lecturaLluvia) + "%</p>";
  pagina += "<p>Humedad del Suelo: " + String(lecturaHumedadSuelo) + "%</p>";
  pagina += "<p>Luz: " + String(lecturaLuz) + "%</p>";
  pagina += "<p>Temperatura: " + String(lecturaTemperatura) + "ºC</p>";
  pagina += "<p>Humedad: " + String(lecturaHumedad) + "%</p>";
  pagina += "</body></html>";
  return pagina;
}

void loop() {
  // Enviar datos a ThingSpeak cada 60 segundos (mínimo permitido)
  static unsigned long previousMillis = 0;
  const long interval = 60000;
  unsigned long currentMillis = millis();

  // Leer sensores
  int lecturaLluvia = map(analogRead(sensorLluvia), 0, 4095, 100, 0);
  int lecturaHumedadSuelo = map(analogRead(sensorHumedadSuelo), 0, 4095, 100, 0);
  int lecturaLuz = map(analogRead(sensorLuz), 0, 4095, 100, 0);
  float lecturaTemperatura = sensorDHT.readTemperature();
  float lecturaHumedad = sensorDHT.readHumidity();
  
  if (currentMillis - previousMillis >= interval) {
    previousMillis = currentMillis;
    
    

    // Enviar datos a ThingSpeak
    if(WiFi.status() == WL_CONNECTED) {
      HTTPClient http;
      String url = "http://api.thingspeak.com/update?api_key=" + apiKey;
      url += "&field1=" + String(lecturaLluvia);
      url += "&field2=" + String(lecturaHumedadSuelo);
      url += "&field3=" + String(lecturaLuz);
      url += "&field4=" + String(lecturaTemperatura);
      url += "&field5=" + String(lecturaHumedad);
      
      http.begin(url);
      int httpResponseCode = http.GET();
      if(httpResponseCode > 0){
        Serial.print("Datos enviados a ThingSpeak, código: ");
        Serial.println(httpResponseCode);
      } else {
        Serial.print("Error al enviar a ThingSpeak: ");
        Serial.println(httpResponseCode);
      }
      http.end();
    }
  }

  // Aquí sigue el código para la funcionalidad del servidor web, control de relé y generación de la página web
  // ...
  
  // (Mantener la funcionalidad original de lectura y respuesta HTTP)
  WiFiClient client = server.available();
  if (client) {
    Serial.println("Nuevo Cliente.");
    String currentLine = "";
    while (client.connected()) {
      if (client.available()) {
        char c = client.read();
        Serial.write(c);
        header += c;
        if (c == '\n') {
          if (currentLine.length() == 0) {
            client.println("HTTP/1.1 200 OK");
            client.println("Content-type:text/html");
            client.println("Connection: close");
            client.println();
            if (header.indexOf("GET /on") >= 0) {
              Serial.println("Relé Encendido");
              digitalWrite(rele, HIGH);
            } else if (header.indexOf("GET /off") >= 0) {
              Serial.println("Relé Apagado");
              digitalWrite(rele, LOW);
            }
            // Generar y enviar la página web (incluye diseño en tonos azules y alertas)
 
            String paginaWeb = crearPaginaWeb(lecturaLluvia, lecturaHumedadSuelo, lecturaLuz, lecturaTemperatura, lecturaHumedad);
            client.println(paginaWeb);
            client.println();
            break;
          } else {
            currentLine = "";
          }
        } else if (c != '\r') {
          currentLine += c;
        }
      }
    }
    header = "";
    client.stop();
    Serial.println("Cliente desconectado.");
    Serial.println("");
  }
}
