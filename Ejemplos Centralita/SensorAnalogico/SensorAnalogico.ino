/**
 * SensorAnalogico.ino - Ejemplo de uso de sensor de señal analógica con la Centralita.
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

const int pinAnalog = 32;

// Inicialización del sketch
void setup() {

    // Inicialización comunicación serial
    Serial.begin(9600);

    // Definición de pines como entradas
    pinMode(pinAnalog, INPUT);

}

// Bucle princiapl del sketch
void loop() {

    const int medidaAnalog = analogRead(pinAnalog);

    Serial.print("Lectura analógica: ");
    Serial.println(medidaAnalog);
    Serial.println();

    delay(500);

}
