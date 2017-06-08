#include <Bridge.h>           //加入Bridge.h程式庫
#include <Temboo.h>          //加入Temboo.h程式庫
#include "TembooAccount.h"    //加入TembooAccount程式庫包含Temboo帳戶訊息

#define Gas_PIN A0
#define Gas_Thre 120

int numRuns = 1;		// 執行計數，如此才能限制執行次數
int maxRuns = 1;		// Choreo 最大執行次數

void setup() {			// 建立初始化區塊
  Serial.begin(9600);		// 設定鮑率為 9600 bps
  
  delay(4000);
  while(!Serial);		// 為了要顯示，等待序列主控台已經連接
  Bridge.begin();		//初始化Bridge
}

void loop() { // 主程式迴圈自動重複動作
  int Gas = analogRead(Gas_PIN);//將感測器針腳讀取到的值儲存在gas變數中
  if (Gas >= Gas_Thre) {	// 如果得到的值小於閥值
if (numRuns <= maxRuns) {	// 如果小於最大執行次數
  		// 顯示執行的choreo及次數
      Serial.println("Running Post - Run #" + String(numRuns++));
      // 宣告PostChoreo物件使用TembooChoreo類別
      TembooChoreo PostChoreo;

      // 初始化並調用Temboo客戶端
      PostChoreo.begin();
    
      // 設定Temboo帳號憑證
      PostChoreo.setAccountName(TEMBOO_ACCOUNT);
      PostChoreo.setAppKeyName(TEMBOO_APP_KEY_NAME);
      PostChoreo.setAppKey(TEMBOO_APP_KEY);
    
      // 設定Choreo所需輸入的資料
      PostChoreo.addInput("Link", "你的連結");
      PostChoreo.addInput("AccessToken", "你的AccessToken ");
      PostChoreo.addInput("Message", "你的訊息");
    
      // 告訴Temboo客戶端要執行哪個Choreo
      PostChoreo.setChoreo("/Library/Facebook/Publishing/Post");
    
      // 執行Choreo，當結果出來，透過序列的方式印出指令的輸出內容
      PostChoreo.run();
    
      while(PostChoreo.available()) {
        char c = PostChoreo.read();
        Serial.print(c);
      }
      PostChoreo.close();
    }

    Serial.println("Waiting...");
    delay(30000); // 等待30秒
}
}

