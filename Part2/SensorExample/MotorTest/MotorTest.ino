#include <Servo.h>
#include <Console.h>
Servo servoRight;
Servo servoLeft;

int action = 0;
int delayTime = 10000;
void setup() {
    Bridge.begin();
    Console.begin();
    while (!Console);
    servoRight.attach(10);
    servoLeft.attach(11);
}
void loop() {
  if (Console.available()) {
    action = Console.parseInt();
    delayTime = Console.parseInt();
    Console.print("action:");
    Console.println(action);
    Console.print("delayTime: ");
    Console.println(delayTime);
  }
  /*if (Console.available() && flag == 1) {
    //action = Console.parseInt();
    delayTime = Console.parseInt();
    //Console.println(action);
    Console.println(delayTime);
  }*/
  
    carStop();
    //forward();
    switch(action)
    {
      case 1:
        forward();
        break;
      case 2:
        backward();
        break;
      case 3:
        turnRight();
        break;
      case 4:
        turnLeft();
        break;
      case 5:
        carStop();
        break;
      case 6:
        forwardRight();
        break;
      case 7:
        forwardLeft();
        break;
      case 8:
        slowForward();
        break;
      /*case 9:
        slowBackward();
        break;*/
      default:
        carStop();
        break;
    }
    
    delay(delayTime);
    
  //}
}
void forward() {
  servoRight.writeMicroseconds(1300);
  servoLeft.writeMicroseconds(1700);
}
void backward() {
  servoRight.writeMicroseconds(1700);
  servoLeft.writeMicroseconds(1300);
}
void turnLeft() {
  servoRight.writeMicroseconds(1300);
  servoLeft.writeMicroseconds(1300);
}
void turnRight() {
  servoRight.writeMicroseconds(1700);
  servoLeft.writeMicroseconds(1700);
}
void carStop() {
  servoRight.writeMicroseconds(1500);
  servoLeft.writeMicroseconds(1500);
}
void forwardRight() {
  servoRight.writeMicroseconds(1450);
  servoLeft.writeMicroseconds(1700);
}
void forwardLeft() {
  servoRight.writeMicroseconds(1300);
  servoLeft.writeMicroseconds(1550);
}
void slowForward() {
  servoRight.writeMicroseconds(1480);
  servoLeft.writeMicroseconds(1520);
}
