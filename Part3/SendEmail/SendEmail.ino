#include <Bridge.h>            //加入Bridge.h程式庫
#include <Temboo.h>           //加入Temboo.h程式庫
#include "TembooAccount.h"     //加入TembooAccount程式庫包含Temboo帳戶訊息

const String GMAIL_USER_NAME = "shuochenghu@gmail.com";
const String GMAIL_PASSWORD = "ktwjnlbsrlpuowql";
const String TO_EMAIL_ADDRESS = "schu@mail.shu.edu.tw";

boolean success = false;       // 設定一個旗標代表是否已經送出信件

void setup() {                 // 建立初始化區塊
  Serial.begin(9600);          // 設定鮑率為 9600 bps

  delay(4000);
  while(!Serial);               // 為了要顯示，等待序列主控台已經連接

  Bridge.begin();              //初始化Bridge
}

void loop()                    // 主程式迴圈自動重複動作
{
  // 只有在我們還沒有成功送出信件時才會送出
  if (!success) {

    Serial.println("Running SendAnEmail...");
    // 宣告SendEmailChoreo物件使用TembooChoreo類別 
    TembooChoreo SendEmailChoreo;
    // 初始化並調用Temboo客戶端
    SendEmailChoreo.begin();
    
    // 設定Temboo帳號憑證
    SendEmailChoreo.setAccountName(TEMBOO_ACCOUNT);
    SendEmailChoreo.setAppKeyName(TEMBOO_APP_KEY_NAME);
    SendEmailChoreo.setAppKey(TEMBOO_APP_KEY);

    // 告訴Temboo客戶端要執行哪個Choreo
    SendEmailChoreo.setChoreo("/Library/Google/Gmail/SendEmail");
    // 輸入你的Gmail帳號
    SendEmailChoreo.addInput("Username", GMAIL_USER_NAME);
    // 輸入你的兩步驟驗證字元密碼.
    SendEmailChoreo.addInput("Password", GMAIL_PASSWORD);
    // 輸入收件人的Email
    SendEmailChoreo.addInput("ToAddress", TO_EMAIL_ADDRESS);
    // 輸入你的信件標題
    SendEmailChoreo.addInput("Subject", "GMAIL傳送測試");

    // 輸入你的信件內容   
    SendEmailChoreo.addInput("MessageBody", "成功接收!");
    // 執行Choreo，當結果出來，透過序列的方式印出指令的輸出內容
    unsigned int returnCode = SendEmailChoreo.run();

    // 回傳收到一個0代表成功
    if (returnCode == 0) {
        Serial.println("Success! Email sent!");
        success = true;
    } else {
      // 若不是收到0代表有錯誤
      // 讀取並列出錯誤訊息
      while (SendEmailChoreo.available()) {
        char c = SendEmailChoreo.read();
        Serial.print(c);
      }
    } 
    SendEmailChoreo.close();

   // 等待60秒再呼叫GetWeatherByAddress
    delay(60000);
  }
}
