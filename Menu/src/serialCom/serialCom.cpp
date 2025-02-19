#include "serialCom.h"

// Caracter ASCII para limpiar pantalla \033[2J\033[H
typedef enum {
    STATUS_IDLE,
    STATUS_INIT,
    STATUS_MENU2,
    STATUS_MENU3,
    STATUS_MENU4
} status_t;

status_t estado = STATUS_INIT;
bool state_changed = true;
static String serialDataBuffer = ""; // Buffer para almacenar datos del puerto serie
static MenuNode *menu = nullptr;

void clearScreen();
void moveCursor(int row, int col);
void serialComInit();
void SerialComUpdate();
char readSerialChar();
void writeSerialComln(String data);
void writeSerialCom(String data);
int serialComAvailable();

void serialComInit() {
    Serial.begin(115200);
    clearScreen();
    menu=menuInit();
    if(menu){
        writeSerialComln("Menu inicializado");
    }else{
        writeSerialComln("Menu no inicializado");
    }
    
    //freeMenu(menu);

}

void SerialComUpdate() {
    char charReceived = readSerialChar();
    

    if (charReceived != '\0' && menu != nullptr) {  // Verificar que el menú está inicializado
        menuUpdate(charReceived, &menu);
        //writeSerialComln(String(*menu->title));
        clearScreen();
        printNode(menu);
    }

}

char readSerialChar() {
    if (Serial.available() > 0) { // Verifica si hay datos disponibles en la terminal serie
        char receivedChar = Serial.read(); // Lee un carácter del buffer serie
        Serial.print(receivedChar); // Imprime el carácter recibido (opcional)
        return receivedChar; // Retorna el carácter leído
    }
    return '\0'; // Retorna un carácter nulo si no hay datos
}

void writeSerialComln(String data) {
    writeSerialCom(data + "\n\r");
}

void writeSerialCom(String data) {
    Serial.print(data);
}

void clearScreen() {
    writeSerialCom("\033[2J\033[H");  // Borra pantalla ANSI
}

void moveCursor(int row, int col) {
    char buffer[10];
    snprintf(buffer, sizeof(buffer), "\033[%d;%dH", row, col);
    writeSerialCom(buffer);
}

int serialComAvailable() {
    return Serial.available();
}
