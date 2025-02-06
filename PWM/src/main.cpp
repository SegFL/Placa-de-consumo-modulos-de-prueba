#include <esp32-hal-ledc.h>
#include <esp32-hal.h>
#include <HardwareSerial.h>
#include "PWM.h"

const int PWM_CHANNEL = 0;       // Canal PWM (ESP32 tiene 16 canales disponibles: 0-15)
const int PWM_FREQ = 312000;     // Frecuencia PWM deseada: 312 kHz
const int PWM_RESOLUTION = 8;    // Resolución de 8 bits (valores de duty cycle entre 0 y 255)

const int MAX_DUTY_CYCLE = (int)(pow(2, PWM_RESOLUTION) - 1); // Valor máximo del duty cycle
const int LED_OUTPUT_PIN = 18;   // Pin GPIO donde se genera la señal PWM

// Variables globales
int dutyCycle = 50;  // Duty cycle inicial (50%)

void setup() {

  PWMInit();
  Serial.begin(115200); // Inicialización del monitor serial

  // Configuración del canal PWM con frecuencia y resolución
  ledcSetup(PWM_CHANNEL, PWM_FREQ, PWM_RESOLUTION);

  // Asociar el canal PWM al pin de salida
  ledcAttachPin(LED_OUTPUT_PIN, PWM_CHANNEL);


}

void loop() {
  // Verificar si hay datos disponibles en la interfaz serial
  if (Serial.available() > 0) {
    char input = Serial.read();  // Leer el carácter ingresado

    // Incrementar o reducir el duty cycle según el símbolo
    if (input == '+') {
      if (dutyCycle < 100) {
        dutyCycle++;  // Incrementar en 1%
      }
    } else if (input == '-') {
      if (dutyCycle > 0) {
        dutyCycle--;  // Reducir en 1%
      }
    }

    // Mostrar el valor actual del duty cycle
    Serial.print("Duty cycle actual: ");
    Serial.print(dutyCycle);
    Serial.println("%");
  }

  // Aplicar el duty cycle actual
  int pwmValue = (dutyCycle * MAX_DUTY_CYCLE) / 100; // Escalar a 0-255
  ledcWrite(PWM_CHANNEL, pwmValue);

  delay(100); // Retardo entre actualizaciones
}
