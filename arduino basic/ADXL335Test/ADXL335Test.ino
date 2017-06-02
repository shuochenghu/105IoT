#define X_PIN A0		// 定義連接X_PIN的針腳	
#define Y_PIN A1		// 定義連接Y_PIN的針腳
#define Z_PIN A2		// 定義連接Z_PIN的針腳

void setup(){			// 建立初始化區塊
  Serial.begin(9600);		// 設定鮑率為 9600 bps
}
float toG(float v){		// 將類比輸入的值轉成g
  return v * 6 / 1023 - 3;
}
void loop(){			// 主程式迴圈自動重複動作
  int x  = analogRead(X_PIN);	// 讀取數值
  int y  = analogRead(Y_PIN);
  int z  = analogRead(Z_PIN);
  
  Serial.print("X: ");		//顯示在Serial Monitor上
  Serial.print(x);
  Serial.print(", Y: ");
  Serial.print(y);
  Serial.print(", Z: ");
  Serial.print(z);
  Serial.print(";  X: ");
  Serial.print(toG(x));
  Serial.print("g, Y: ");
  Serial.print(toG(y));
  Serial.print("g, Z: ");
  Serial.print(toG(z));
  Serial.println("g");
  delay(100);
}

