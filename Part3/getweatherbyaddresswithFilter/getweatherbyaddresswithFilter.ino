#include <Bridge.h>		//加入Bridge.h程式庫
#include <Temboo.h>		//加入Temboo.h程式庫
#include "TembooAccount.h"//加入TembooAccount程式庫包含Temboo帳戶訊息

int numRuns = 1;		// 執行計數，如此才能限制執行次數
int maxRuns = 10;		// Choreo 最大執行次數

void setup() {			// 建立初始化區塊
  Serial.begin(9600); 		// 設定鮑率為 9600 bps
  delay(4000);
  while(!Serial);		// 為了要顯示，等待序列主控台已經連接
  Bridge.begin();		//初始化Bridge
}

void loop() {			// 主程式迴圈自動重複動作
  if (numRuns <= maxRuns) {	// 如果小於最大執行次數
	// 顯示執行的choreo及次數
    Serial.println("Running GetWeatherByAddress - Run #" + String(numRuns++));

    // 宣告GetWeatherByAddressChoreo物件使用TembooChoreo類別
    TembooChoreo GetWeatherByAddressChoreo;

    // 初始化並調用Temboo客戶端
    GetWeatherByAddressChoreo.begin();
    
    // 設定Temboo帳號憑證
    GetWeatherByAddressChoreo.setAccountName(TEMBOO_ACCOUNT);
    GetWeatherByAddressChoreo.setAppKeyName(TEMBOO_APP_KEY_NAME);
    GetWeatherByAddressChoreo.setAppKey(TEMBOO_APP_KEY);
    
    // 設定Choreo所需輸入的資料
    GetWeatherByAddressChoreo.addInput("Units", "c");
    GetWeatherByAddressChoreo.addInput("Address", "taipei");
    
    // 告訴Temboo客戶端要執行哪個Choreo
    GetWeatherByAddressChoreo.setChoreo("/Library/Yahoo/Weather/GetWeatherByAddress");

    // 增加一個輸出過濾器來提取目前的溫度
    GetWeatherByAddressChoreo.addOutputFilter("temperature", "/rss/channel/item/yweather:condition/@temp", "Response");
    // 增加一個輸出過濾器來從最新的資料中提取日期和時間
    GetWeatherByAddressChoreo.addOutputFilter("date", "/rss/channel/item/yweather:condition/@date", "Response");
    
    // 執行Choreo，當結果出來，透過序列的方式印出指令的輸出內容
    GetWeatherByAddressChoreo.run();
    
    while(GetWeatherByAddressChoreo.available()) {
      char c = GetWeatherByAddressChoreo.read();
      Serial.print(c);
    }
    GetWeatherByAddressChoreo.close();
  }

  Serial.println("Waiting...");
  delay(30000);			// 等待30秒再呼叫GetWeatherByAddress
}

