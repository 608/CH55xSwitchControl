/**
* 1ボックス分のポケモンを全て逃がす
* 
* 初期条件は以下の通り
* 1.メニューを開いていないこと
* 2.Xボタンを押したときに「ポケモン」が左上から1つ右の場所にあること
*/
#include <CH55xSwitchControl.h>

// ボックスを開く
void openBox() {
  pushButton(BUTTON_X, 1000);
  holdHat(HAT_LEFT_UP, 1000);
  pushHat(HAT_RIGHT, 500);
  pushButton(BUTTON_A, 2000);
  pushButton(BUTTON_R, 2000);
}

// ボックス内の今いるカーソルにいるポケモンを逃がす
void releasePokemon() {
  pushButton(BUTTON_A, 500);
  pushHatLoop(HAT_UP, 500, 2);
  pushButton(BUTTON_A, 1000);
  pushHat(HAT_UP, 500);
  pushButton(BUTTON_A, 1000);
  pushButtonLoop(BUTTON_A, 300, 4);
}

void setup() {
  // USBコントローラーの初期化
  USBInit();

  // Switchにマイコンを認識させる為に適当なボタン処理を行う
  pushButtonLoop(BUTTON_B, 100, 10);

  // 開始
  openBox();
  for (int release_poke_num = 0; release_poke_num < 30; release_poke_num++) {
    // ポケモンを逃がす
    releasePokemon();
    // カーソルを次のポケモンの場所に移動させる
    pushHat(HAT_RIGHT, 500);
    if (release_poke_num % 6 == 5) {
      pushHat(HAT_DOWN, 500);
      pushHat(HAT_RIGHT, 500);
    }
  }
}

void loop() {
}