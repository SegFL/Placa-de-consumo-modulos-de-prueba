
#include "ina219.h"

// Crear una instancia del sensor INA219


void setup() {
    // Iniciar la comunicación serie para depuración

    ina219Init();
    // Inicializar la comunicación I2C y el sensor INA219

}

void loop() {


  ina219Update();

  delay(1000);
}
