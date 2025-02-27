/**
 * LedRgb.ino - Ejemplo de uso de LED RGB de la Centralita
 * 
 * Creado el 16/10/2023 por Kevin Rosa - kevin.ingenieria@digitalcodesign.com
 * 
 * Encendido secuencial y combinado de los colores del RGB de la Centralita.
 *
 * Conexiones conectores:
 *   -> Diodo Rojo: PIN27.
 *   -> Diodo Verde: PIN26.
 *   -> Diodo Azul: PIN25.
 */

const int pinRojo = 27;
const int pinVerde = 26;
const int pinAzul = 25;

// Inicialización del sketch
void setup() {

    // Definición de pines como salida
    pinMode(pinRojo, OUTPUT);
    pinMode(pinVerde, OUTPUT);
    pinMode(pinAzul, OUTPUT);

    // Inicializar pines apagados
    digitalWrite(pinRojo, LOW);
    digitalWrite(pinVerde, LOW);
    digitalWrite(pinAzul, LOW);

}

// Bucle principal del sketch
void loop() {

    // Encendemos el color rojo
    digitalWrite(pinRojo, HIGH);
    digitalWrite(pinVerde, LOW);
    digitalWrite(pinAzul, LOW);
    delay(500);

    // Encendemos el color rojo y el verde
    digitalWrite(pinRojo, HIGH);
    digitalWrite(pinVerde, HIGH);
    digitalWrite(pinAzul, LOW);
    delay(500);

    // Encendemos el color verde
    digitalWrite(pinRojo, LOW);
    digitalWrite(pinVerde, HIGH);
    digitalWrite(pinAzul, LOW);
    delay(500);

    // Encendemos el color verde y el azul
    digitalWrite(pinRojo, LOW);
    digitalWrite(pinVerde, HIGH);
    digitalWrite(pinAzul, HIGH);
    delay(500);

    // Encendemos el color Azul
    digitalWrite(pinRojo, LOW);
    digitalWrite(pinVerde, LOW);
    digitalWrite(pinAzul, HIGH);
    delay(500);

    // Encendemos el color azul y el rojo
    digitalWrite(pinRojo, HIGH);
    digitalWrite(pinVerde, LOW);
    digitalWrite(pinAzul, HIGH);
    delay(500);

}
