#include <Wire.h>
#include "RTClib.h"

RTC_DS1307 rtc;

void setup() {
  Serial.begin(9600);
  
  rtc.begin();
  rtc.adjust(DateTime(__DATE__, __TIME__));     //Se establece la fecha y hora
}

void loop() {
  DateTime fecha = rtc.now();     //Se define la variable fecha como y se le asigna la fecha y hora actual     

  Serial.print(fecha.day());      //Las siguientes lineas imprimen la fecha y hora     
  Serial.print("/");       
  Serial.print(fecha.month());     
  Serial.print("/");       
  Serial.print(fecha.year());      
  Serial.print(" ");       
  Serial.print(fecha.hour());     
  Serial.print(":");       
  Serial.print(fecha.minute());     
  Serial.print(":");       
  Serial.println(fecha.second());  

  delay(5000);
}
