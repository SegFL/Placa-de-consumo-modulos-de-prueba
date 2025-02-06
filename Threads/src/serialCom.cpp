

#include "serialCom.h"

typedef enum{
    IDLE,    //estado default
    CONNECTING_WIFI     
} serialComState_t;

static serialComState_t currentState=IDLE;

static String serialDataBuffer = ""; // Buffer para almacenar datos del puerto serie

void serialComInit(){
    Serial.begin(115200); // Inicializa el puerto serie para depuración
}


char readSerialChar() {
    if (Serial.available() > 0) { // Verifica si hay datos disponibles en la terminal serie
        char receivedChar = Serial.read(); // Lee un carácter del buffer serie
        Serial.print(receivedChar); // Imprime el carácter recibido (opcional)
        return receivedChar; // Retorna el carácter leído
    }
    return '\0'; // Retorna un carácter nulo si no hay datos
}


void writeSerialComln(String data){
    writeSerialCom(data+"\n\r");
}
void writeSerialCom(String data){
    Serial.print(data);
}



void SerialComUpdate(){

    return;
}



void serialComUpdate(){
    char receivedChar = readSerialChar();
    if(receivedChar!='\0'){
        if(receivedChar!='\r'){
            if(receivedChar!='\n'){
                serialDataBuffer+=receivedChar;
            }else{
            //Serial.println(serialDataBuffer);//Para chequear que se imprima porpantalla(provoca un doble loopback)
                serialDataBuffer="";
            }
        }
       
    }
}

//Codigo bloqueante para recivir un String
bool receiveString(String data){
    
    char receivedChar = readSerialChar();
    if(receivedChar!='\0'){
        if(receivedChar!='\n'){
            data+=receivedChar;
        }else{
            //Serial.println(serialDataBuffer);//Para chequear que se imprima porpantalla(provoca un doble loopback)
            return true;
        }
    }
}