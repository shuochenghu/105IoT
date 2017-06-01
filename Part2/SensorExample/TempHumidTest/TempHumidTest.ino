#include <DHT.h>		//加入DHT.h程式庫
#include <Console.h>

unsigned long duration=100;
unsigned long frequency=3000;
float hum;  			//濕度
float temp;			//溫度
int light;			//亮度

DHT dht(6,DHT11);		//宣告dht物件使DHT類別並定義感測器針腳及類型

void setup() {			// 建立初始化區塊
  Bridge.begin();
  Console.begin();
  while(!Console);
  dht.begin();			//初始化dht11 
}

void loop() {			// 主程式迴圈自動重複動作
  hum=dht.readHumidity();	//將讀取到的溼度資料儲存在hum變數中
  temp=dht.readTemperature();	//將讀取到的溫度資料儲存在temp變數中
  light=analogRead(A0);		//將讀取到的亮度資料純存在light變數中

  if (temp > 30) {
    //for (duration=15; duration>=1; duration--) {
      //for (frequency=2000; frequency<=2500;frequency+=20) {
          tone(8,frequency,duration);
      //}
    //}
  }

  
  Console.print("Temperature: "); //將資料顯示在Console Monitor上
  Console.print(temp);
  Console.print("oC Humidity: ");
  Console.print(hum);
  Console.print("% Light level: ");
  Console.println(light);  
  delay(1000);			//暫停1秒
}

