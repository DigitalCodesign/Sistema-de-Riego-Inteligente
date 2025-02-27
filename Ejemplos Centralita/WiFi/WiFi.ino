/**
 * WiFi.ino - Ejemplo de uso del WiFi de la Centralita.
 * 
 * Creado el 18/10/2023 por Kevin Rosa - kevin.ingenieria@digitalcodesign.com
 * 
 * Crear un servidor web donde poder conectarse para controlar
 * del relé de la Centralita y monitorizar los valores de los sensores
 * de lluvia, humedad del suelo y luminosidad.
 */

#include <WiFi.h>
#include <DHT.h>

// Creamos el Servidor Web en el puerto 80
WiFiServer server(80);

// Variables con las credenciales del WiFi
const char* ssid     = "MiFibra-7D98";
const char* password = "NoVFC2RR";

// Variable para gestionar el timeout de conexión a la red WiFi
int contconexion = 0;

// Variable para guardar la petición HTTP
String header;

// Creamos el sensor DHT
DHT sensorDHT(17, DHT22);

// Variable relativa con la salida del Relé
const int rele = 4;

// Vairables con los pines de los sensores de lluvia, humedad del suelo y luminosidad
const int sensorLluvia = 32;
const int sensorHumedadSuelo = 33;
const int sensorLuz = 34;

// Código HTML para la interfaz mostrada en la IP del Servidor Web
String inicioPagina = "<!DOCTYPE html>"
    "<html>"
    "<head>"
    "<meta charset='utf-8' />"
    "<title>Servidor Web ESP32</title>"
    "</head>"
    "<body>"
    "<center>";

String finPagina = "</center></body></html>";


// Inicialización del ESP32
void setup() {

    // Inicializar monitor serial
    Serial.begin(115200);
    Serial.println("");

    // Definición e inicialización del relé de salida y sensores
    pinMode(sensorLluvia, INPUT);
    pinMode(sensorHumedadSuelo, INPUT);
    pinMode(sensorLuz, INPUT);
    pinMode(rele, OUTPUT);
    digitalWrite(rele, LOW);

    // Inicializar Sensor DHT
    sensorDHT.begin();

    // Inicio de la conexión WiFi con las credenciales
    WiFi.begin(ssid, password);

    // Intenta la conexión, si llega al timeout cancela
    while (WiFi.status() != WL_CONNECTED and contconexion <50) { 
        ++contconexion;
        delay(500);
        Serial.print(".");
    }

    // Detectar si se pudo realizar la conexión al WiFi o no
    if (contconexion < 50) {
     
        // Mostrar IP obtenida en la conexión del WiFi
        Serial.println("");
        Serial.println("WiFi conectado");
        Serial.println(WiFi.localIP());

        // Inicializamos el Servidor Web
        server.begin();

    } else { 

        // No se pudo conectar a la red
        Serial.println("");
        Serial.println("Error de conexion");

    }

}

// Bucle principal de funcionamiento
void loop(){

    // Esperamos conexiones entrantes en la IP del Servidor Web
    WiFiClient client = server.available();

    // Si detectamos un cliente conectado
    if (client) {

        Serial.println("New Client.");
        String currentLine = "";

        // Mantenemos en el bucle mientras el cliente esté conectado
        while (client.connected()) {

            // Comprobar si el cliente se encuentra disponible
            if (client.available()) {

                // Preparar variables para leer petición del cliente
                char c = client.read();
                Serial.write(c);
                header += c;

                // Si el byte es un caracter de salto de línea
                if (c == '\n') {

                    // Y la nueva línea está vacía, es el fin de la petición
                    if (currentLine.length() == 0) {

                        // Respondemos a la petición con código HTTP 200 OK
                        client.println("HTTP/1.1 200 OK");
                        client.println("Content-type:text/html");
                        client.println("Connection: close");
                        client.println();
            
                        // Si la petición viene por ruta /on, encendemos el Relé
                        if (header.indexOf("GET /on") >= 0) {

                            Serial.println("GPIO on");
                            digitalWrite(rele, HIGH);

                        // Si la petición viene por ruta /off, apagamos el Relé
                        } else if (header.indexOf("GET /off") >= 0) {

                            Serial.println("GPIO off");
                            digitalWrite(rele, LOW);

                        }

                        int lecturaLluvia = map(analogRead(sensorLluvia), 0, 4095, 0, 100);
                        int lecturaHumedadSuelo = map(analogRead(sensorHumedadSuelo), 0, 4095, 0, 100);
                        int lecturaLuz = map(analogRead(sensorLuz), 0, 4095, 0, 100);
                        float lecturaTemperatura = sensorDHT.readHumidity();
                        float lecturaHumedad = sensorDHT.readTemperature();

                        String titulo = "<h1>Servidor Web ESP32</h1>";
                        String botonEncendido = "<p><a href='/on'><button style='height:50px;width:100px'>ON</button></a></p>";
                        String botonApagado = "<p><a href='/off'><button style='height:50px;width:100px'>OFF</button></a></p>";
                        String valoresSensorLluvia = "<p>Lluvia: " + String(lecturaLluvia) + "% | ";
                        String valoresSensorLuz = "Luz: " + String(lecturaHumedadSuelo) + "% | ";
                        String valoresSensorTemp = "Temperatura: " + String(lecturaTemperatura) + "ºC | ";
                        String valoresSensorHum = "Humedad relativa: " + String(lecturaHumedad) + "% | ";
                        String valoresSensorHumSuelo = "Humedad del Suelo: " + String(lecturaLuz) + "%</p>";

                        String web = inicioPagina;
                        web += titulo;
                        web += botonEncendido;
                        web += botonApagado;
                        web += valoresSensorLluvia;
                        web += valoresSensorLuz;
                        web += valoresSensorTemp;
                        web += valoresSensorHum;
                        web += valoresSensorHumSuelo;
                        web += finPagina;

                        // Envía la interfaz Web
                        client.println(web);

                        // Terminamos la respuesta HTTP con una línea en blanco
                        client.println();

                        // Terminamos el bucle
                        break;

                    // Limpiamos la línea actual
                    } else {

                        currentLine = "";

                    }

                // Cuando llega un retorno de carro, agregamos a la línea actual
                } else if (c != '\r') {

                    currentLine += c;

                }

            }

        }

        // Limpiamos la variable header
        header = "";

        // Cerramos la conexión con el cliente
        client.stop();
        Serial.println("Client disconnected.");
        Serial.println("");

    }

}
