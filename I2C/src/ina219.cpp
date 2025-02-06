#include "ina219.h"



Adafruit_INA219 ina219;

void ina219Init(){
    // Iniciar la comunicación serie para depuración


    Serial.begin(115200);
    while (!Serial) {
        delay(1); // Esperar a que el puerto serie esté listo
    }
    Serial.println("Inicializando INA219...");

    //Crea una conexion I2C con el sensor
    if (!ina219.begin()) {
        Serial.println("No se pudo encontrar el sensor INA219. Verifica las conexiones.");
        while (1) { delay(10); } // Detener ejecución si no se encuentra el sensor
    }

    // Configuración opcional del rango del sensor
    ina219.setCalibration_16V_400mA(); // Configuración para 32V y 2A
    Serial.println("INA219 inicializado correctamente.");


}


void ina219Update(){

    // Leer el voltaje del bus
    float busVoltage = ina219.getBusVoltage_V();

    // Leer el voltaje del shunt
    float shuntVoltage = ina219.getShuntVoltage_mV();

    // Leer la corriente en mA
    float current_mA = ina219.getCurrent_mA();

    // Leer la potencia en mW
    float power_mW = ina219.getPower_mW();


    Serial.print("Voltaje Bus: "); Serial.print(busVoltage); Serial.println(" V");
    Serial.print("Voltaje Shunt: "); Serial.print(shuntVoltage); Serial.println(" mV");
    Serial.print("Corriente: "); Serial.print(current_mA); Serial.println(" mA");
    Serial.print("Potencia: "); Serial.print(power_mW); Serial.println(" mW");
    Serial.println("-----------------------------------");

    // Esperar 1 segundo antes de la siguiente lectura
    
}