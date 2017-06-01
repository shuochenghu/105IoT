 //加入三軸加速器
#include <Bridge.h>			//加入Bridge.h程式庫
#include <YunServer.h>			//加入YunServer.h程式庫
#include <YunClient.h>			//加入YunClient.h程式庫
#include <Process.h>			//加入Process.h程式庫
#include <Servo.h>      //加入Servo.h程式庫

//int DigitalPin[] = {12, 13};         // 定義LED針腳，取消pin2(PIR)
//int AnalogPin[] = {0,1,2,3};            // 定義類比針腳
//int DacPin = 3;                         // 定義要做PWM輸出的針腳
//int dac = 0;                            // 定義PWM的初始值
YunServer server;			//Yun的網路伺服器監聽預設在port 5555將會發送所有HTTP指令給我們

Process WebCam;                         // 宣告WebCam物件使用Process類別
//Servo servoLeft;			// 宣告servoleft物件使用Servo類別
//Servo servoRight;			// 宣告servoright物件使用Servo類別

void setup() {				// 建立初始化區塊
  //pinMode(2, INPUT);			//設定右邊PIR為輸入
  //pinMode(4, INPUT);   //左邊避帳紅外線
  //pinMode(5, INPUT);   //右邊避帳紅外線
  //pinMode(7, INPUT);   //下方巡跡防跌紅外線 
  //pinMode(DacPin, OUTPUT);		//設定右邊觸鬚為輸入
  //pinMode(12, OUTPUT);			//設定綠色LED為輸入
  pinMode(13, OUTPUT);			//設定紅色LED為輸入
  //servoLeft.attach(11);			// 連接左邊馬達的訊號到PIN 11
  //servoRight.attach(10);		// 連接右邊馬達的訊號到PIN 10
  digitalWrite(13, LOW);		// 透過燈號改變知道bridge開始運作

  Bridge.begin();			// 初始化Bridge，連接ATmega和AR9331
  server.listenOnLocalhost();		// 只監聽連接本地主機的指令，不能連接其他額外的網路

  server.begin();
  delay(10000);                          //等待Linux開機完全再輸入指令
  //開啟視訊串流
  WebCam.runShellCommandAsynchronously("mjpg_streamer -i \"input_uvc.so -d /dev/video0 -r 320x240 -f 25\" -o \"output_http.so -p 8080 -w /www/webcam\" &");

  while (WebCam.running());

  digitalWrite(13, HIGH);
} //end of setup()

void loop() {
 
} //end of loop()



