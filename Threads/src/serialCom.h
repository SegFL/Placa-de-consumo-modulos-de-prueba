#include <Arduino.h>

void serialComInit();
char readSerialChar();
void writeSerialCom(String data);
void writeSerialComln(String data);
void serialComUpdate();
String receiveString();
//Permite soliciar la comunicacion serie
