#include <Process.h>		//加入Process.h程式庫

void setup() {			// 建立初始化區塊
  Bridge.begin();		// 初始化 Bridge
  Serial.begin(9600);		// 設定鮑率為 9600 bps
  while (!Serial);		// 等待直到連接到Serial Monitor
  runCurl();			// 執行副程式
  runCpuInfo();
}

void loop() {			// 主程式迴圈自動重複動作
}

void runCurl() {
  // 送出「curl」指令並從網路取得用文字拼成的Aduino標誌。
  // cURL是一個利用URL語法在命令列下工作的檔案傳輸工具
  Process p;			// 宣告p物件使用Process類別
  p.begin("curl");		// Process 送出「curl」指令
  // 在「curl」後面加入一個URL參數
  p.addParameter("http://temp.shu.edu.tw/upload/0OBt95Dw01/asciilogo.txt"); 
  p.run();			// 執行並等待它停止

  // 透過序列的方式印出arduino的標誌
  // 這個輸出可以用串流的方法讀出
  while (p.available() > 0) {
    char c = p.read();
    Serial.print(c);
  }
  Serial.flush(); 		// 確認資料的最後一個位元已經被送出
}

void runCpuInfo() {
  // 送出「cat /proc/cpuinfo」指令 (顯示Atheros CPU資訊)
  // 「cat」是個顯示檔案內容的指令
  Process p;			// 宣告p物件使用Process類別
  p.begin("cat");		// Process 送出「cat」指令
  p.addParameter("/proc/cpuinfo");	// 加入cpu資訊檔案路徑當作cat的參數
  p.run();			// 執行並等待它停止

  // 透過序列的方式印出指令的輸出內容
  // 這個輸出可以用串流的方法讀出
  while (p.available() > 0) {
    char c = p.read();
    Serial.print(c);
  }
  Serial.flush();		// 確認資料的最後一個位元已經被送出
}

