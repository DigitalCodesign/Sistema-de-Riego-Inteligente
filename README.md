# Sistema-de-Riego-Inteligente

Estos códigos de ejemplo están construidos por Digital Codesign para utilizar junto con el kit educacional "Sistema de Monitorización y Riego Inteligente".

Puedes encontrar nuestro Kit y mucho más material de electrónica y robótica en nuestra tienda oficial: https://digitalcodesign.com/shop

# Ejemplos de Control y Monitoreo con Centralita

Este repositorio contiene una colección de ejemplos de código para interactuar con una Centralita, demostrando diversas funcionalidades de control y monitoreo.

## Ejemplos

### Bluetooth

-   **Descripción:** Establece un canal de comunicación bidireccional entre la Centralita y dispositivos Bluetooth. Permite la transmisión y recepción de datos a través del monitor serie, facilitando la interacción inalámbrica con el sistema.
-   **Uso:** Ideal para aplicaciones que requieren comunicación inalámbrica con otros dispositivos Bluetooth, como smartphones o sensores remotos.

### LedRgb

-   **Descripción:** Demuestra el control del LED RGB integrado en la Centralita. Permite generar diferentes colores mediante secuencias de encendido y combinaciones de colores primarios.
-   **Uso:** Perfecto para crear indicadores visuales, efectos de iluminación o para señalizar el estado del sistema.

### Rele

-   **Descripción:** Proporciona un control básico del relé de la Centralita. Permite implementar secuencias de encendido y apagado para controlar dispositivos externos.
-   **Uso:** Fundamental para automatizar el control de dispositivos como bombas de riego, luces o cualquier otro equipo eléctrico.

### SensorAnalogico

-   **Descripción:** Se centra en la lectura de sensores analógicos. Permite capturar y transmitir los valores medidos por los sensores a través del monitor serie.
-   **Uso:** Útil para monitorizar variables como la luminosidad, la humedad del suelo o cualquier otro sensor que proporcione una salida analógica.

### SensorAnalogicoDigital

-   **Descripción:** Similar al ejemplo anterior, pero para sensores que ofrecen tanto lecturas analógicas como digitales. Permite leer y transmitir ambos tipos de datos.
-   **Uso:** Versátil para sensores con múltiples modos de salida, proporcionando una mayor flexibilidad en la monitorización.

### SensorDHT

-   **Descripción:** Diseñado específicamente para el sensor DHT, muestra cómo recopilar datos de temperatura y humedad, y transmitirlos para su monitorización.
-   **Uso:** Esencial para aplicaciones de monitoreo ambiental, como estaciones meteorológicas o sistemas de control climático.

### WiFi

-   **Descripción:** Guía en la creación de un servidor web para la Centralita. Permite controlar el relé y monitorizar datos de sensores en tiempo real a través de una interfaz web.
-   **Uso:** Ideal para crear sistemas de control y monitoreo remotos, accesibles desde cualquier dispositivo con un navegador web.

## Uso General

Cada ejemplo incluye un archivo de código fuente con comentarios explicativos. Para utilizar los ejemplos:

1.  Clona este repositorio en tu máquina local.
2.  Abre el archivo del ejemplo deseado en tu IDE de Arduino.
3.  Conecta los componentes necesarios a tu Centralita.
4.  Carga el código en la Centralita.
5.  Abre el monitor serie (si es necesario) o accede a la interfaz web (para el ejemplo WiFi) para ver los resultados.

## Contribución

¡Las contribuciones son bienvenidas! Si tienes ideas para nuevos ejemplos o mejoras para los existentes, no dudes en abrir un "pull request" o una "issue".
