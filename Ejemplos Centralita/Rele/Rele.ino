/**
 * SalidaRiego.ino - Ejemplo de uso del relé para activar riego con la Centralita.
 * 
 * Creado el 16/10/2023 por Kevin Rosa - kevin.ingenieria@digitalcodesign.com
 * 
 * Encendido y apagado secuencial de la salida con el relé.
 */

const int rele = 4;

// Inicialización del sketch
void setup() {

    // Definición de pines como entradas
    pinMode(rele, OUTPUT);

    // Establecer el pin en apagado
    digitalWrite(rele, LOW);

}

// Bucle princiapl del sketch
void loop() {

    // Encendido y apagado secuencial cada segundo
    digitalWrite(rele, HIGH);
    delay(1000);
    digitalWrite(rele, LOW);
    delay(1000);

}
