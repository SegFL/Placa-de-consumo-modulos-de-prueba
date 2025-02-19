#include <Arduino.h>
#include "serialCom/serialCom.h"








void setup() {
  serialComInit();

  //freeMenu(menu);

  

}

void loop() {
  SerialComUpdate();

}

