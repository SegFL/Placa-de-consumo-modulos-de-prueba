#include <Wire.h>
#include <Adafruit_INA219.h>
#include <HardwareSerial.h>

// Crear objeto INA219
Adafruit_INA219 ina219;

void setup() {
    // Iniciar la comunicación serie para depuración
    Serial.begin(115200);
    while (!Serial) {
        delay(1); // Esperar a que el puerto serie esté disponible
    }
    Serial.println("Inicializando INA219...");

    // Inicializar I2C e INA219
    if (!ina219.begin()) {
        Serial.println("No se pudo encontrar el sensor INA219. Verifica la conexión.");
        while (1) { delay(10); }
    }

    // Configuración opcional
    ina219.setCalibration_32V_2A(); // Configuración de rango
    Serial.println("INA219 inicializado correctamente.");
}

void loop() {
    // Leer voltaje del bus
    float busVoltage = ina219.getBusVoltage_V();

    // Leer corriente en amperios
    float current_mA = ina219.getCurrent_mA();

    // Leer potencia en miliwatts
    float power_mW = ina219.getPower_mW();

    // Leer voltaje del shunt
    float shuntVoltage = ina219.getShuntVoltage_mV();

    // Mostrar datos en el monitor serie
    Serial.print("Voltaje Bus: "); Serial.print(busVoltage); Serial.println(" V");
    Serial.print("Voltaje Shunt: "); Serial.print(shuntVoltage); Serial.println(" mV");
    Serial.print("Corriente: "); Serial.print(current_mA); Serial.println(" mA");
    Serial.print("Potencia: "); Serial.print(power_mW); Serial.println(" mW");
    Serial.println("-----------------------------------");

    // Esperar 1 segundo antes de la siguiente lectura
    delay(1000);
}
