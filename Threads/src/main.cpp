#include <Arduino.h>
#include "serialCom.h"

// Definimos los manejadores de las tareas
TaskHandle_t Task1Handle = NULL;
TaskHandle_t Task2Handle = NULL;

// Función de la tarea 1
void Task1(void *pvParameters) {
  while (true) {
    Serial.println("Task 1 is running");
    char receivedChar=readSerialChar();
    if(receivedChar!='\0'){
        Serial.print("Recivi un caracter");
        Serial.println(String(receivedChar));

    }
    vTaskDelay(pdMS_TO_TICKS(10)); // Espera 1 segundo
  }
}

// Función de la tarea 2
void Task2(void *pvParameters) {
  while (true) {
    Serial.println("Task 2 is running");
    vTaskDelay(pdMS_TO_TICKS(50)); // Espera 0.5 segundos
  }
}

void setup() {
  serialComInit();
  delay(1000);
  Serial.println("Starting FreeRTOS tasks...");

  Serial.println("Inicie serialComInit() desde el setup()");

  // Crear la tarea 1
  xTaskCreate(
    Task1,          // Función que implementa la tarea
    "Task1",        // Nombre de la tarea
    1000,           // Tamaño del stack en palabras
    NULL,           // Parámetro que se pasa a la tarea
    1,              // Prioridad de la tarea
    &Task1Handle    // Manejador de la tarea
  );

  // Crear la tarea 2
  xTaskCreate(
    Task2,          // Función que implementa la tarea
    "Task2",        // Nombre de la tarea
    1000,           // Tamaño del stack en palabras
    NULL,           // Parámetro que se pasa a la tarea
    1,              // Prioridad de la tarea
    &Task2Handle    // Manejador de la tarea
  );
}

void loop() {
  // El bucle principal puede estar vacío si no lo necesitas

}
