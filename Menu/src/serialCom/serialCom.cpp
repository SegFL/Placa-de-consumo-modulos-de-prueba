

#include "serialCom.h"


typedef enum {
    STATUS_IDLE,
    STATUS_INIT,
    STATUS_MENU2,
    STATUS_MENU3,
    STATUS_MENU4
} status_t;

status_t estado=STATUS_INIT;
bool state_changed=true;
static String serialDataBuffer = ""; // Buffer para almacenar datos del puerto serie


void updateSerialState(char caracter);


void serialComInit(){
    Serial.begin(115200); // Inicializa el puerto serie para depuración
}

void updateSerialState(char caracter){
    if(caracter!='\0'){
        switch(estado){
            case STATUS_INIT:{
                if(caracter=='x'){
                    //writeSerialComln("Entro al menu 2");
                    estado=STATUS_MENU2;
                }else if(caracter==27){//27 es el ASCI de ESC
                    estado= STATUS_INIT;
                }
            }state_changed=true;break;
            case STATUS_MENU2:{
                switch(caracter){
                    case 'a':{
                        estado=STATUS_MENU3;
                    }break;
                    case 'b':{
                        estado=STATUS_MENU4;
                    }break;
                    case 27:{
                        estado=STATUS_INIT;
                    }break;
                }
            }state_changed=true;break;
            case STATUS_MENU3:{
                
            }state_changed=true;break;
            case STATUS_MENU4:{
                
            }state_changed=true;break;
        }

    }

}
void SerialComUpdate(){

    char charReceived =readSerialChar();

    updateSerialState(charReceived);
    switch(estado){
        case STATUS_INIT:{
            if(state_changed==true){
                writeSerialComln("Se imprimio STATUS_INIT");
                state_changed=false;
            }
        }
        case STATUS_MENU2:{
            if(state_changed==true){
                writeSerialComln("Se imprimio STATUS_MENU2");
                state_changed=false;
            }
        }
        case STATUS_MENU3:{
            if(state_changed==true){
                writeSerialComln("Se imprimio STATUS_MENU3");
                state_changed=false;
            }
        }
        case STATUS_MENU4:{
            if(state_changed==true){
                writeSerialComln("Se imprimio STATUS_MENU4");
                state_changed=false;
            }
        }
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


void writeSerialComln(String data){
    writeSerialCom(data+"\n\r");
}
void writeSerialCom(String data){
    Serial.print(data);
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

//Codigo **bloqueante** para recivir un String
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

int serialComAvailable(){
    return Serial.available();
}