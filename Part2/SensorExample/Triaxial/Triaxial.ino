#include <Console.h>
#define X_PIN A3		// 定義連接X_PIN的針腳	
#define Y_PIN A2		// 定義連接Y_PIN的針腳
#define Z_PIN A1		// 定義連接Z_PIN的針腳
int ledPin = 13;

void setup(){			// 建立初始化區塊
  //Serial.begin(9600);		// 設定鮑率為 9600 bps
  Bridge.begin();
  Console.begin();
  while(!Console);
  pinMode(ledPin, OUTPUT);
}
float toG(float v){		// 將類比輸入的值轉成g
  return v * 6 / 1023 - 3;
}
void loop(){			// 主程式迴圈自動重複動作
  int x  = analogRead(X_PIN);	// 讀取數值
  int y  = analogRead(Y_PIN);
  int z  = analogRead(Z_PIN);
  Console.println("Srart");

  if (y<=320)
     digitalWrite(ledPin, HIGH);
  else
     digitalWrite(ledPin, LOW);
  Console.print("X: ");		//顯示在Console Monitor上
  Console.print(x);
  Console.print(", Y: ");
  Console.print(y);
  Console.print(", Z: ");
  Console.print(z);
  Console.print(";  X: ");
  Console.print(toG(x));
  Console.print("g, Y: ");
  Console.print(toG(y));
  Console.print("g, Z: ");
  Console.print(toG(z));
  Console.println("g");
  delay(3000);
}

