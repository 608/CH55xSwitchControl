/**
 * スプラトゥーン3のヒーローモードでイクラ集めを自動化するスケッチ
 *
 * ※ 当プログラムはスプラトゥーン3のVer1.1.1で動作確認を行っております。アップデートにより正常に動作しなくなる可能性がありますのでご了承ください。
 *
 * 初期条件は以下の通り
 * 1. ヒーローモードで「宇宙の中心が、ここにある。」のヤカン上にいること
 * 2. Rスティックの操作感度が「0」であること
 * 3. Rスティックの上下操作が「ノーマル」であること
 * 3. ジャイロ操作が「OFF」であること
 */
#include <CH55xSwitchControl.h>

// ヤカンに潜る際のロード時間
#define START_LOADING_TIME_MS 10000

// ミッションをクリアした後、自由行動できるようになるまでの時間
#define CLEAR_LOADING_TIME_MS 30000

// リッターを構えるまでの時間
#define ADJUST_TIME_MS 6000

// 「使いたいコントローラーのL+Rを押してください」を閉じる
void selectController() {
  pushButton(BUTTON_L, 100);
  pushButton(BUTTON_R, 100);
  pushButton(BUTTON_A, 3000);
}

// ミッションを開始する
void startMission() {
  pushButtonContinuous(BUTTON_ZL, START_LOADING_TIME_MS);
  pushButton(BUTTON_A, 2000);
  tiltJoystick(0, -100, 0, 0, 2000);
  pushButton(BUTTON_A, 3000);
}

// インクを発射する
void shootInk() {
  tiltJoystick(0, 0, 0, -100, 50);
  pushButtonContinuous(BUTTON_ZR, 2000);
}

void setup() {
  // USBコントローラーの初期化
  USBInit();

  // Switchにマイコンを認識させる為に適当なボタン処理を行う
  pushButtonLoop(BUTTON_B, 100, 10);

  // 「使いたいコントローラーのL+Rを押してください」の画面が出るまで待機する
  delay(5000);

  // 「使いたいコントローラーのL+Rを押してください」を突破する
  selectController();
}

void loop() {
    startMission();
    delay(ADJUST_TIME_MS);
    shootInk();
    delay(CLEAR_LOADING_TIME_MS);
}