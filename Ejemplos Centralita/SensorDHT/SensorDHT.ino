/**
 * SensorDHT.ino - Ejemplo de uso de sensor DHT-22 con la Centralita.
 * 
 * Creado el 16/10/2023 por Kevin Rosa - kevin.ingenieria@digitalcodesign.com
 * 
 * Envío periódico del valor medido por el sensor a través del monitor serie.
 *
 * Conexiones conectores:
 *   -> Sensor de Lluvia; 1-Vcc, 2-PIN13, 3-PIN32, 4-GND.
 *   -> Sensor Humedad Suelo; 1-Vcc, 2-PIN16, 3-PIN33, 4-GND.
 *   -> Sensor Humedad-Temperatura DHT-22; 1-Vcc, 2-PIN17, 3-NC, 4-GND.
 *   -> Sensor Luminosidad; 1-Vcc, 2-PIN18, 3-PIN34, 4-GND.
 *   -> Conector Analógico-Digital; 1-Vcc, 2-PIN19, 3-PIN35, 4-GND.
 *   -> Conector Digital; 1-Vcc, 2-PIN23, 3-NC, 4-GND.
 *   -> Conector I2C; 1-Vcc, 2-PIN21, 3-PIN22, 4-GND.
 */

#include "DHT.h"

const int pinDigital = 17;

// Inicializamos el objeto del DHT-22
DHT dht22(pinDigital, DHT22);

// Inicialización del sketch
void setup() {

    // Inicialización comunicación serial
    Serial.begin(9600);

    // Inicialización sensor DHT-22
    dht22.begin();

}

// Bucle princiapl del sketch
void loop() {

    float humedad = dht22.readHumidity();
    float temperatura = dht22.readTemperature();

    Serial.print("Humedad: ");
    Serial.println(humedad);
    Serial.print("Temperatura: ");
    Serial.println(temperatura);
    Serial.println();

    delay(500);

}
