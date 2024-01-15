#include <WiFi.h>
#include <HTTPClient.h>
#include <ArduinoJson.h>
#include <M5CoreS3.h>

const char* openai_endpoint = "https://api.openai.com/v1/chat/completions";

extern const char* API_KEY;
extern const char* WIFI_SSID;
extern const char* WIFI_PASSWORD;

void setup() {
  M5.begin();
  M5.Lcd.print("Hello World");
  // Wi-Fi接続
  WiFi.begin(WIFI_SSID, WIFI_PASSWORD);
  while (WiFi.status() != WL_CONNECTED) {
    delay(1000);
    M5.Lcd.print(".");
  }
  M5.Lcd.print("ok!");

  // HTTPリクエストの準備
  HTTPClient http;
  http.begin(openai_endpoint);
  http.addHeader("Content-Type", "application/json");
  http.addHeader("Authorization", "Bearer " + String(API_KEY));

  // JSONデータの作成
  String postData = "{\"model\": \"gpt-4\", \"messages\": [{\"role\": \"user\", \"content\": \"hello world!!\"}]}";

  // POSTリクエストの送信
  int httpResponseCode = http.POST(postData);

  // レスポンスの取得
  if (httpResponseCode > 0) {
    String response = http.getString();

    // JSONデータの解析
    DynamicJsonDocument doc(1024); // 必要に応じてサイズを調整
    deserializeJson(doc, response);

    // 'choices'フィールドの抽出
    JsonArray choices = doc["choices"];
    for (JsonObject choice : choices) {
      String text = choice["message"]["content"].as<String>();
      M5.Lcd.print(text);
    }
  } else {
    M5.Lcd.print(httpResponseCode);
  }

  // 接続終了
  http.end();
}

void loop() {
  // ここでは何もしません
}