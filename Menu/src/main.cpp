#include <Arduino.h>
#include "serialCom/serialCom.h"




#define QUEUE_LENGTH 100       // Máximo número de elementos en la queue
#define ITEM_SIZE sizeof(char) // Tamaño de cada elemento (en este caso, 1 byte para un char)

QueueHandle_t xQueueComSerial;         // Handle para la queue
TaskHandle_t Task1Handle = NULL;




// Función de la tarea 1 RECIVE DATOS
void Task1(void *pvParameters) {
  String buffer="";
  char receivedChar='\0';
  while (true) {
            // Simula leer datos de la interfaz serie
    SerialComUpdate();
        // Simular un retardo
    vTaskDelay(pdMS_TO_TICKS(10)); // Espera 1 segundo
  }
}


void setup() {
 
  serialComInit();
      // Crear la queue
    xQueueComSerial = xQueueCreate(QUEUE_LENGTH, ITEM_SIZE);
    
    // Verificar si la queue se creó correctamente
    if (xQueueComSerial == NULL)
    {
        // Manejar error: No se pudo crear la queue
        printf("Error: No se pudo crear la queue.\n");
        while (1); // Detener el sistema o manejarlo según sea necesario
    }


    // Crear la tarea 1
  xTaskCreate(
    Task1,          // Función que implementa la tarea
    "Task1",        // Nombre de la tarea
    1000,           // Tamaño del stack en palabras
    NULL,           // Parámetro que se pasa a la tarea
    1,              // Prioridad de la tarea
    &Task1Handle    // Manejador de la tarea
  );

}

void loop() {
  // put your main code here, to run repeatedly:
}

