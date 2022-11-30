// 引用元：
// SV自動化スレ >>109氏
// http://nozomi.2ch.sc/test/read.cgi/poke/1669303704/109

//-事前準備-
//・増殖したミライドンに増やしたいアイテムを持たせる
//・ボックスを1に合わせる
//・ポケモンを2匹。先頭を任意のポケモン、2番目を増殖したミライドンにする
//・メニューを開いてミライドンにカーソルを合わせた状態（画像参照）

//-終了後-
//・ライドフォームのミライドンをバトルフォームにする操作を行う



// ライブラリを読み込むためのコード
#include <CH55xSwitchControl.h>

// マイコンのセット時に1度だけ行われる処理
void setup(){
  // USBコントローラーの初期化
  USBInit();

  // Switchがマイコンを認識するまでは信号を受け付けないため、適当な処理をさせておく
  pushButtonLoop(BUTTON_Y, 100, 10);
}

// ここに記述した内容がループされ続ける
void loop(){
  //増殖ミラコラをライドフォルムに戻す
  pushButton(BUTTON_A, 500);
  pushHat(HAT_UP, 400);
  pushHat(HAT_UP, 400);
  pushButton(BUTTON_A, 1200);
  pushButton(BUTTON_A, 800);
  pushButton(BUTTON_A, 3000);
  pushButton(BUTTON_A, 800);

  //ミラコラボックスにアクセス
  pushHat(HAT_UP, 400);
  pushHat(HAT_RIGHT, 400);
  pushButton(BUTTON_A, 2000);
  pushButton(BUTTON_X, 400);
  pushButton(BUTTON_X, 400);
  pushButton(BUTTON_L, 400);

  //もちものをしまう
  pushButton(BUTTON_A, 500);
  pushHat(HAT_DOWN, 200);
  pushHat(HAT_DOWN, 200);
  pushHat(HAT_DOWN, 200);
  pushButton(BUTTON_A, 500);

  //カーソルを初期位置に戻す
  pushButton(BUTTON_B, 2000);
  pushHat(HAT_LEFT, 1000);
}
