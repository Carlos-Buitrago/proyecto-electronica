#include <Servo.h>

Servo servo1;

int PINSERVO = 2;

void setup() {
  servo1.attach(PINSERVO);
}

void loop() {
  servo1.write(0);
  delay(8000);
  servo1.write(180);
  delay(8000);
}
