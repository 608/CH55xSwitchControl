/**
* 巣穴からワットを回収し続けるスケッチ
*
* 初期条件は以下の通り
* 1. 願いのかたまりを投げ入れた巣穴の前にいること
* 2. 巣穴のワットは回収済みであること
* 3. Switchの本体設定で「インターネットで時間をあわせる」がOFFになっていること
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
  pushHat(HAT_DOWN, 25);
  if (hasNintendoSwitchOnlineMenu()) {
    pushHatLoop(HAT_RIGHT, 25, 5);
  } else {
    pushHatLoop(HAT_RIGHT, 25, 4);
  }
  pushButton(BUTTON_A, 100);

  // 設定 > 本体 > 日付と時刻
  holdHat(HAT_DOWN, 2000);
  pushHat(HAT_RIGHT, 25);
  if (hasDockUpdateMenu()) {
    pushHatLoop(HAT_DOWN, 25, 9);
  } else {
    pushHatLoop(HAT_DOWN, 25, 4);
  }
  pushButton(BUTTON_A, 200);

  // 日付と時刻 > 現在の日付と時刻
  pushHatLoop(HAT_DOWN, 25, 2);
  pushButton(BUTTON_A, 500);
  pushHatLoop(HAT_RIGHT, 25, 2);
  pushHat(HAT_UP, 25);
  pushHatLoop(HAT_RIGHT, 25, 3);
  pushButton(BUTTON_A, 50);

  // ホーム画面 > ゲーム画面
  pushButton(BUTTON_HOME, 600);
  pushButton(BUTTON_A, 600);
}

void wattGain() {
  // 募集開始
  pushButton(BUTTON_A, 3000);

  // 日付変更
  changeDate();

  // レイド募集中止
  pushButton(BUTTON_B, 1000);
  pushButton(BUTTON_A, 6000);

  // ワット回収
  pushButton(BUTTON_A, 1000);
  pushButton(BUTTON_B, 1000);
  pushButton(BUTTON_A, 1000);
}

void setup() {
  // USBコントローラーの初期化
  USBInit();

  // Switchにマイコンを認識させる為に適当なボタン処理を行う
  pushButtonLoop(BUTTON_B, 500, 4);

  // 開始
  pushButton(BUTTON_A, 1000);
}

void loop() {
  wattGain();
}