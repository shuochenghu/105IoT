#include <Servo.h>
#include <Console.h>
Servo servoRight;
Servo servoLeft;
//for echo
const int trig = 5;
const int echo = 6;
const int inter_time = 500;
//int time = 0;

//for motor
//int action = 0;
//int delayTime = 10000;
void setup() {
    Bridge.begin();
    Console.begin();
    while (!Console);
    servoRight.attach(10);
    servoLeft.attach(11);

    pinMode (trig, OUTPUT);
    pinMode (echo, INPUT);
}
void loop() {
    float duration, distance;
    digitalWrite(trig, HIGH);
    delayMicroseconds(1000);
    digitalWrite(trig, LOW);
    duration = pulseIn (echo, HIGH);
    distance = (duration/2)/29;
    //Console.print("Data:");
    //Console.print (time/1000);
    Console.print(", d = ");
    Console.print(distance);
    Console.println(" cm");
    //time = time + inter_time;

    if (distance < 20)
      turnRight();
    else
      forward(); 
    
    delay(inter_time);    
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
