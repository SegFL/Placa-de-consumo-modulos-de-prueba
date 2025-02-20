#include <Arduino.h>
#include <HardwareSerial.h>




void serialComInit();
char readSerialChar();
void writeSerialCom(String data);
void writeSerialComln(String data);
//String receiveString();
void SerialComUpdate();
int serialComAvailable();


void clearScreen();

void serialComInit();
char readSerialChar();
void writeSerialComln(String data);
void writeSerialCom(String data);


