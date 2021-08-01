#include <Arduino.h>
#include <LiquidCrystal.h>      //Lib LCD
#include <Servo.h>              //Lib Servo
#include <Wire.h>               //Lib I2C
#include <RTClib.h>             //Lib RTC

LiquidCrystal lcd(7, 6, 5, 4, 3, 2);    //Iniciacion LCD

int buzzerPin = 13;                     //Pin Buzzer

Servo motorServo;                          //Iniciacion Servo
int servoPos = 0;
int servoPin = 10;

RTC_DS1307 rtc;                         //Iniciacion RTC
DateTime now;
byte hour, minute;
String h, m;

int horaComer = 14;                     //Variables hora de comer
int minutoComer = 0;
boolean tiempoComer = true;

int buttonPin = 11;                     //----BOTON INICIO----

void setup() {
  pinMode(buzzerPin, OUTPUT);           //Setup
  lcd.begin(16, 2);
  rtc.begin();
  pinMode(buttonPin, INPUT_PULLUP);    //----BOTON INICIO----
}

void loop() {                           //Loop principal
  now = rtc.now();                      //Se imprime la hora actual (Se llama a la funcion printTime())
  printTime(now);                       

  if(digitalRead(buttonPin) == LOW){    //----BOTON INICIO----
    comer();
  }
}

void comer(){                           //Funcion comer
  lcd.clear();
  lcd.setCursor(0,0);
  lcd.print("Sirviendo comida");

  motorServo.attach(servoPin);          //Activacion servo
  
  for(servoPos = 0; servoPos <= 180; servoPos += 1){        //Se abre la tapa
    motorServo.write(servoPos);
    delay(15);
  }

  delay(1000);

  for(servoPos = 180; servoPos >= 0; servoPos -= 1){        //Se cierra la tapa
    motorServo.write(servoPos);
    delay(15);
  }

  delay(1000);

  motorServo.detach();                   //Desactivacion servo

  alarma();                              //Se llama a la funcion alarma
}

void alarma(){                           //Funcion alarma
  for (int i = 0; i < 3; i++){
    tone(buzzerPin, 1915);
    delay(700);
    tone(buzzerPin, 1700);
    delay(700);
    tone(buzzerPin, 1519);
    delay(700);
    noTone(buzzerPin);

      
    lcd.clear();
    lcd.setCursor(0, 0);
    lcd.print("La comida");
    lcd.setCursor(0, 1);
    lcd.print("esta servida!");

    delay(2000);

    now = rtc.now();
    printTime(now);

    delay(5000);
  }
}

void printTime(DateTime s){               //Funcion printTime()
  lcd.setCursor(0, 0);
  lcd.print("Hora: ");                    //Se printea la hora actual
  hour = s.hour();
  if (hour < 10){                         //Se formatean las horas <10
    h = "0" + String(hour);
  }
  else {
    h = String(hour);
  }
  lcd.print(h);
  lcd.print(':');
  minute = s.minute();
  if (minute < 10){
    m = "0" + String(minute);
  }
  else{
    m = String(minute);
  }
  lcd.print(m);
  
  lcd.setCursor(0, 1);                    //Se printea la hora de la comida
  lcd.print("Siguiente: XXXX");

  return;
}
