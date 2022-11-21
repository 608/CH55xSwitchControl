/**
* 育て屋から卵を回収→孵化→ボックスに預けるを繰り返すスケッチ
* ボックスに空きがある限り、ポケモンを孵化し続ける
*
* 初期条件は以下の通り
* 1.ハシノマはらっぱにいること
* 2.自転車に乗っていること
* 3.手持ちが1体のみのこと
* 4.Xボタンを押したときに「タウンマップ」が左上、「ポケモン」がその右にあること
* 5.ボックスが空のこと
*/
#include <CH55xSwitchControl.h>

#define TIME_TO_HATCHING_SEC 120

// 空飛ぶタクシーでハシノマはらっぱに移動
void moveToInitialPlayerPosition() {
  pushButton(BUTTON_X, 1000);
  holdHat(HAT_UP_LEFT, 1000);
  pushButton(BUTTON_A, 2500);
  pushButtonLoop(BUTTON_A, 1500, 2);
  delay(2000);
}

// 初期位置から育て屋さんに移動し卵を受け取る
void getEggFromBreeder() {
  // 初期位置(ハシノマはらっぱ)から育て屋さんのところまで移動
  pushButton(BUTTON_PLUS, 1000);
  tiltRightStick(STICK_MAX, STICK_NEUTRAL, 2000, BUTTON_NONE);
  tiltLeftStick(166, STICK_MIN, 800, BUTTON_NONE);
  pushButton(BUTTON_PLUS, 1000);

  // 育て屋さんから卵をもらう
  pushButtonLoop(BUTTON_A, 1000, 4);
  pushButtonLoop(BUTTON_B, 500, 10);
}

// 初期位置(ハシノマはらっぱ)からぐるぐる走り回る
void runAround(int run_time_sec) {
  // delayの秒数がintの最大値を越えないように30秒ごとに実行する
  for (int i = 0; i < run_time_sec / 30; i++) {
    tiltLeftAndRightStick(STICK_MAX, STICK_MAX, STICK_MIN, STICK_MIN, 30000, BUTTON_NONE);
  }
  tiltLeftAndRightStick(STICK_MAX, STICK_MAX, STICK_MIN, STICK_MIN, (run_time_sec % 30) * 1000, BUTTON_NONE);
}

// 卵が孵化するのを待つ
void waitEggHatching() {
  pushButtonLoop(BUTTON_B, 500, 40);
}

// 孵化した手持ちのポケモンをボックスに預ける
// box_line : 何列目にポケモンを預けるか
void sendHatchedPoemonToBox(int box_line) {
  // ボックスを開く
  pushButton(BUTTON_X, 1000);
  holdHat(HAT_UP_LEFT, 1000);
  pushHat(HAT_RIGHT, 500);
  pushButton(BUTTON_A, 2000);
  pushButton(BUTTON_R, 2000);

  // 手持ちの孵化したポケモンを範囲選択
  pushHat(HAT_LEFT, 500);
  pushHat(HAT_DOWN, 500);
  pushButtonLoop(BUTTON_Y, 500, 2);
  pushButton(BUTTON_A, 500);
  holdHat(HAT_DOWN, 2000);
  pushButton(BUTTON_A, 500);

  // ボックスに移動させる
  pushHatLoop(HAT_RIGHT, 500, box_line + 1);
  pushHat(HAT_UP, 500);
  pushButton(BUTTON_A, 500);

  // ボックスを閉じる
  pushButtonLoop(BUTTON_B, 1500, 3);
}

// ボックスを次のボックスに移動させる
void moveToNextBox() {
  // ボックスを開く
  pushButton(BUTTON_X, 1000);
  holdHat(HAT_UP_LEFT, 1000);
  pushHat(HAT_RIGHT, 500);
  pushButton(BUTTON_A, 2000);
  pushButton(BUTTON_R, 2000);

  // ボックスを移動
  pushHat(HAT_UP, 500);
  pushHat(HAT_RIGHT, 500);

  // ボックスを閉じる
  pushButtonLoop(BUTTON_B, 1500, 3);
}

// 手持ちが1体の状態から、卵受け取り→孵化を繰り返す
void reciveAndHatchEggs() {
  for (int egg_num = 0; egg_num < 5; egg_num++) {
    moveToInitialPlayerPosition();
    getEggFromBreeder();
    moveToInitialPlayerPosition();
    runAround(TIME_TO_HATCHING_SEC);
    waitEggHatching();
  }
}

// 孵化シーケンスを実行
void hatching() {
  for (int box_line = 0; box_line < 6; box_line++) {
    reciveAndHatchEggs();
    sendHatchedPoemonToBox(box_line);
  }
  moveToNextBox();
}

void setup() {
  // USBコントローラーの初期化
  USBInit();

  // Switchにマイコンを認識させる為に適当なボタン処理を行う
  pushButtonLoop(BUTTON_B, 500, 5);

  // 初めの卵が出現するまで走り回る
  moveToInitialPlayerPosition();
  runAround(20);
}

void loop() {
  hatching();
}
