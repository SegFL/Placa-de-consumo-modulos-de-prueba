
#include "userInterface.h"


static MenuNode *menu = nullptr;

void moveCursor(int row, int col);

void userInterfaceInit(){
    serialComInit();
    clearScreen();//Borra mensajes del ESP32 al iniciar el programa
    menu=menuInit();
    if(menu){
        writeSerialComln("Menu inicializado");
    }else{
        writeSerialComln("Menu no inicializado");
    }
}


void userInterfaceUpdate(){
    char charReceived = readSerialChar();

    if (charReceived != '\0' && menu != nullptr) {  // Verificar que el menú está inicializado
        menuUpdate(charReceived, &menu);
        //writeSerialComln(String(*menu->title));
        clearScreen();
        printNode(menu);
    }
}