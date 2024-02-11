#include <M5GFX.h>

static M5GFX lcd;                     // LGFXのインスタンスを作成。
static LGFX_Sprite sprite(&lcd);      // lcdに描画するスプライト作成
static LGFX_Sprite sprite2(&sprite);  // spriteに描画するスプライト作成
static LGFX_Sprite sprite3;  // デフォルト描画先設定がないスプライト作成

void setup() {
  lcd.init();
  sprite.createSprite(64, 64);
  sprite2.createSprite(32, 32);
  sprite3.createSprite(16, 16);
  sprite.fillScreen(TFT_RED);
  sprite2.fillScreen(TFT_BLUE);
  sprite3.fillScreen(TFT_GREEN);
  sprite3.pushSprite(&sprite2, 0, 0);
  sprite2.pushSprite(0, 0);
  sprite.pushSprite(0, 0);
}

void loop() {}
