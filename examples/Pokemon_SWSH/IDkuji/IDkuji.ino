/**
* IDくじを引き続けるスケッチ
*
* 初期条件は以下の通り
* 1.ランクマバグを使用し、使える状態であること
* 2.ポケセンのロトミの前でゲーム画面のままUSBを挿すこと
*/
#include <CH55xSwitchControl.h>

// Nintendo Switchのシステムバージョンを設定する
#define SWITCH_SYSTEM_VERSION 13

// Nintendo Switch Liteの場合はtrueを設定する
#define IS_SWITCH_LITE false

// ホーム画面にSwitchのVer11から登場した Nintendo Switch Onlineのメニューが存在するか
bool hasNintendoSwitchOnlineMenu(void) {
  return SWITCH_SYSTEM_VERSION >= 11;
}

// 設定 > 本体 に ドックの更新 メニューが存在するか
bool hasDockUpdateMenu(void) {
  if (IS_SWITCH_LITE) {
    return false;
  } else {
    return SWITCH_SYSTEM_VERSION >= 13;
  }
}

void changeDate() {
  // ホーム画面 > 設定
  pushButton(BUTTON_HOME, 500);
  pushHatButton(HAT_DOWN, 25);
  if (hasNintendoSwitchOnlineMenu()) {
    pushHatButtonLoop(HAT_RIGHT, 25, 5);
  } else {
    pushHatButtonLoop(HAT_RIGHT, 25, 4);
  }
  pushButton(BUTTON_A, 100);

  // 設定 > 本体 > 日付と時刻
  pushHatButtonContinuous(HAT_DOWN, 2000);
  pushHatButton(HAT_RIGHT, 25);
  if (hasDockUpdateMenu()) {
    pushHatButtonLoop(HAT_DOWN, 25, 9);
  } else {
    pushHatButtonLoop(HAT_DOWN, 25, 4);
  }
  pushButton(BUTTON_A, 200);

  // 日付と時刻 > 現在の日付と時刻
  pushHatButtonLoop(HAT_DOWN, 25, 2);
  pushButton(BUTTON_A, 500);
  pushHatButtonLoop(HAT_RIGHT, 25, 2);
  pushHatButton(HAT_UP, 25);
  pushHatButtonLoop(HAT_RIGHT, 25, 3);
  pushButton(BUTTON_A, 50);

  // ホーム画面 > ゲーム画面
  pushButton(BUTTON_HOME, 600);
  pushButton(BUTTON_A, 600);
}

void drawIDkuji() {
  //ロトミ起動 > IDくじ
  pushButtonLoop(BUTTON_A, 1000, 2);
  pushHatButton(HAT_DOWN, 150);
  pushButtonLoop(BUTTON_A, 100, 20);
  pushButtonLoop(BUTTON_B, 250, 60);
}

void setup() {
  // USBコントローラーの初期化
  USBInit();

  // Switchにマイコンを認識させる為に適当なボタン処理を行う
  pushButtonLoop(BUTTON_B, 100, 10);
}

void loop() {
  drawIDkuji();
  changeDate();
}