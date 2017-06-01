 //加入三軸加速器
#include <Bridge.h>			//加入Bridge.h程式庫
#include <YunServer.h>			//加入YunServer.h程式庫
#include <YunClient.h>			//加入YunClient.h程式庫
#include <Process.h>			//加入Process.h程式庫
#include <Servo.h>                      //加入Servo.h程式庫

int DigitalPin[] = {12, 13};         // 定義LED針腳，取消pin2(PIR)
int AnalogPin[] = {0,1,2,3};            // 定義類比針腳

YunServer server;			//Yun的網路伺服器監聽預設在port 5555將會發送所有HTTP指令給我們

Process WebCam;                         // 宣告WebCam物件使用Process類別

void setup() {				// 建立初始化區塊
  pinMode(12, OUTPUT);			//設定綠色LED為輸入
  pinMode(13, OUTPUT);			//設定紅色LED為輸入
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
  YunClient client = server.accept();  // 從伺服器取得Client  
  if (client) {				// 是否是新client?
    process(client);      // 如果是的話，跳入process副程式處理指令
    client.stop();			// 關閉連接並釋放資源
  }
  delay(50);				// 每隔50毫秒輪詢一次
} //end of loop()

void process(YunClient client) {
  String command = client.readStringUntil('/');	// 讀取指令，讀取指令的字串直到遇到 / 符號
  
  if (command == "status") {		// 是"status"指令? (回報個接腳狀態)
    statusCommand(client);		// 是的話執行statusCommand副程式
  }
}   // end of process()

void statusCommand(YunClient client) {
  int pin, value;
  //讀取所有針腳的狀態並輸出成
  //"status#2=0#12=0#13=1#3=190#A0=24"的格式
  client.print(F("status"));
  
  //數位針腳狀態
  for (int thisPin = 0; thisPin < 2; thisPin++) {
    pin = DigitalPin[thisPin];
    value = digitalRead(pin);
    client.print(F("#"));		// 傳送回傳訊息到client
    client.print(pin);
    client.print(F("="));
    client.print(value);
  }
  
  //類比輸入針腳狀態
  for (int thisPin = 0; thisPin < 4; thisPin++) {
    pin = AnalogPin[thisPin];
    value = analogRead(pin);
    client.print(F("#A"));    // 傳送回傳訊息到client
    client.print(pin);
    client.print(F("="));
    client.print(value);
  }
  client.println("");
}  //end of statusCommand()




