#include <Bridge.h>		// 加入Bridge.h程式庫
#define Gas_PIN A0		// 定義感測器針腳

void setup(){			// 建立初始化區塊
    Bridge.begin();		// 初始化Bridge
    Serial.begin(9600);		// 設定鮑率為 9600 bps
    while (!Serial);		// 為了要顯示，等待序列主控台已經連接
}

void loop(){			// 主程式迴圈自動重複動作
  int gas = analogRead(Gas_PIN);//將感測器針腳讀取到的值儲存在gas變數中
  
  Serial.print("MQ4's Value: ");	// 顯示數值
  Serial.println(gas);

  delay(1000);			// 暫停1秒
}

