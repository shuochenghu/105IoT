#include <Bridge.h>		//加入Bridge.h程式庫
#include <Temboo.h>		//加入Temboo.h程式庫
#include "TembooAccount.h"//加入TembooAccount程式庫包含Temboo帳戶訊息

/*** 替換成你的帳號資料 ***/
// 如果有安全疑慮或為了可重複使用可以用#define來指定資料並存在一個.h檔中

const String GMAIL_USER_NAME = "你的gmail帳號";
const String GMAIL_PASSWORD = "你的兩步驟驗證16字元密碼";
const String TO_EMAIL_ADDRESS = "收件人的E-mail";


boolean success = false;	// 建立一個標記來告訴我們是否送出email

#define X_PIN A0		// 定義連接X_PIN的針腳
#define Y_PIN A1		// 定義連接Y_PIN的針腳
#define Z_PIN A2		// 定義連接Z_PIN的針腳


void setup() {			// 建立初始化區塊
  Serial.begin(9600);		// 設定鮑率為 9600 bps
  delay(4000);			// 為了要顯示，等待序列主控台已經連接
  while(!Serial);

  Bridge.begin();		//初始化Bridge
}

void loop()			// 主程式迴圈自動重複動作
{
  int x  = analogRead(X_PIN);	// 讀取數值
  int y  = analogRead(Y_PIN);
  int z  = analogRead(Z_PIN);
  Serial.print("X=");		//顯示在Serial Monitor上
  Serial.println(x);
  Serial.print("Y=");
  Serial.println(y);
  Serial.print("Z=");
  Serial.println(z);
  if ((x>256)|| (y>256)||(z>256)){  //設定震動幅度，若超過則送出E-mail
    Serial.println("Running SendAnEmail...");
  // 宣告SendEmailChoreo物件使用TembooChoreo類別
    TembooChoreo SendEmailChoreo; 

    // 初始化並調用Temboo客戶端
    //要注意每次run()被呼叫後客戶端必須重新被調用，重新填入適當的參數
    SendEmailChoreo.begin();
    
    // 設定Temboo帳號憑證
    SendEmailChoreo.setAccountName(TEMBOO_ACCOUNT);
    SendEmailChoreo.setAppKeyName(TEMBOO_APP_KEY_NAME);
    SendEmailChoreo.setAppKey(TEMBOO_APP_KEY);

    // 告訴Temboo客戶端要執行哪個Choreo(Google > Gmail > SendEmail)
    SendEmailChoreo.setChoreo("/Library/Google/Gmail/SendEmail");
 

    // 設定Choreo所需輸入的資料
    // 請參考https://www.temboo.com/library/Library/Google/Gmail/SendEmail/
   
    // 你的gmail帳號
    SendEmailChoreo.addInput("Username", GMAIL_USER_NAME);
    // 你的兩步驟驗證16字元密碼
    SendEmailChoreo.addInput("Password", GMAIL_PASSWORD);
    // 收件人的E-mail
    SendEmailChoreo.addInput("ToAddress", TO_EMAIL_ADDRESS);
    // 你的信件標題
    SendEmailChoreo.addInput("Subject", "ALERT: Shock detected");

     // 你的信件內容
    SendEmailChoreo.addInput("MessageBody", "warning,Shock detected");

    // 執行Choreo，將回傳碼儲存在returnCode變數中，若為0則代表成功
    unsigned int returnCode = SendEmailChoreo.run();

    // returnCode變數若為0則代表成功
    if (returnCode == 0) {
        Serial.println("Success! Email sent!");
        success = true;
    } else {
      // 不為0則代表有錯誤，讀取並印出錯誤碼
      while (SendEmailChoreo.available()) {
        char c = SendEmailChoreo.read();
        Serial.print(c);
      }
    } 
    SendEmailChoreo.close();

    // 停止60秒
    delay(60000);
  }
  delay(1000);
}

