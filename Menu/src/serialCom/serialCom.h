#include <Arduino.h>
#include <menuTree/menuTree.h>



void serialComInit();
char readSerialChar();
void writeSerialCom(String data);
void writeSerialComln(String data);
//String receiveString();
void SerialComUpdate();
int serialComAvailable();
