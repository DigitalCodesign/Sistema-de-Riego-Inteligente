/**
 * Bluetooth.ino - Ejemplo de uso del Bluetooth de la Centralita
 * 
 * Creado el 18/10/2023 por Kevin Rosa - kevin.ingenieria@digitalcodesign.com
 * 
 * Envía por monitor serial lo que recibe por Bluetooth y viceversa de manera continuada.
 */

#include <BluetoothSerial.h>

// Objeto Bluetooth Serial
BluetoothSerial SerialBT;

// Inicialización del sketch
void setup() {

    // Inicialización del monitor serial y Bluetooth
    Serial.begin(9600);
    SerialBT.begin("ESP32");

    Serial.println("Dispositivo arrancado, disponible para conexión por Bluetooth!");

}

// Bucle principal del sketch
void loop() {

    // Leer entrada del monitor serial y enviar por Bluetooth
    if (Serial.available()) {

        SerialBT.write(Serial.read());

    }

    // Leer entrada del Bluetooth y enviar por monitor serial
    if(SerialBT.available()) {

        Serial.write(SerialBT.read());

    }

    delay(100);

}
