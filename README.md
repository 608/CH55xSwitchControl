# CH55xSwitchControl

安価で入手できる中国製マイコンのCH552を使用してNintendo Switchを自動化する為のArduino IDE用ライブラリです。

<img src="https://user-images.githubusercontent.com/21293572/202479479-fff6e791-59a1-463b-bc7a-f67b4cd12cca.jpg" width="50%">

## 必要なもの
**ハードウェア**
- CH552マイコンボード
    - USBシリアル変換機能の搭載したマイコンボードをBoothにて販売しています。
- マイコンボードとNintendo Swicthを接続するUSBケーブル

**ソフトウェア**
- Arduino IDE

## 使い方
### 環境設定
**ライブラリーのインストール**  
Arduinoのライブラリのあるディレクトリ(/Users/{username}/Documents/Arduino/libraries/ など)に、このレポジトリをcloneする/ダウンロードして展開する。


**ch55xduinoのインストール**  
Arduino IDEでCH552マイコンを使用する為に必要となる。
1. ファイル→環境設定を開き、「追加のボードマネージャのURL」に以下のURLを追加する。
~~~
https://raw.githubusercontent.com/DeqingSun/ch55xduino/ch55xduino/package_ch55xduino_mcs51_index.json
~~~

2. ツール→ボード→ボードマネージャを開き、検索窓で「ch」と入力して出てくる「ch55xduino」を選んでインストールする。

3. ツール→ボードから、CH552を選択する。


**入力**  
ライブラリを使いたいファイルの先頭に以下のように記載してください。

~~~
#include <CH55xSwitchControl.h>
~~~

## コマンド一覧

### ボタン

- ボタンを押すコマンド

  - `pushButton(uint16_t button, uint32_t delay_time)`

    - button: 押すボタン
    - delay_time: ボタンを押した後の待ち時間（1 秒 = 1000）
    
  - `pushButtonLoop(uint16_t button, uint32_t delay_time, uint16_t loop_count)`

    - button: 押すボタン
    - delay_time: ボタンを押した後の待ち時間（1 秒 = 1000）
    - loop_count: ボタンを押す回数

  - 使用例

    ```
    pushButton(BUTTON_HOME);        // HOMEボタンを入力する
    pushButton(BUTTON_A, 500);      // Aボタンを入力後、0.5秒待機する
    pushButtonLoop(BUTTON_B, 3000, 10); // 3秒おきにBボタンを入力する、それを10回繰り返す
    ```

- ボタンを長押しするコマンド

  - `holdButton(uint16_t button, uint32_t hold_time)`

    - button: 押し続けるボタン
    - hold_time: ボタンを押す時間の長さ（1 秒 = 1000）

  - 使用例

    ```
    holdButton(BUTTON_L, 2000);       // Lボタンを2秒間押し続けてから離す
    holdButton(BUTTON_CAPTURE, 1500); // キャプチャーボタンを1.5秒間押し続けてから離す
    ```

- `BUTTON` 定義一覧

  ```
  BUTTON_NONE
  BUTTON_Y
  BUTTON_B
  BUTTON_A
  BUTTON_X
  BUTTON_L
  BUTTON_R
  BUTTON_ZL
  BUTTON_ZR
  BUTTON_MINUS
  BUTTON_PLUS
  BUTTON_LCLICK
  BUTTON_RCLICK
  BUTTON_HOME
  BUTTON_CAPTURE
  ```

### 十字キー（方向ボタン）

- 十字キー（方向ボタン）を押すコマンド

  - `pushHat(uint8_t hat, uint32_t delay_time);`

    - hat: 押す十字キーのボタン
    - delay_time: ボタンを押した後の待ち時間（1 秒 = 1000）

  - `pushHatLoop(uint8_t hat, uint32_t delay_time, uint16_t loop_count);`

    - hat: 押す十字キーのボタン
    - delay_time: ボタンを押した後の待ち時間（1 秒 = 1000）
    - loop_count: ボタンを押す回数
    
  - 使用例

    ```
    pushHat(HAT_UP);          // 上キーを1回だけ入力する
    pushHat(HAT_LEFT, 1000);  // 左キーを入力後、1秒待機する
    pushHatLoop(HAT_DOWN, 25, 5); // 0.25秒おきに下キーを入力する、それを5回繰り返す
    ```

- 十字キー（方向ボタン）を長押しするコマンド

  - `holdHat(uint8_t hat, uint32_t hold_time);`

    - hat: 押し続ける十字キーのボタン
    - hold_time: ボタンを押す時間の長さ（1 秒 = 1000）

  - 使用例

    ```
    holdHat(HAT_RIGHT, 5000);   // 右キーを5秒間押し続けてから離す
    holdHat(HAT_UP_LEFT, 2500); // 十字キーを左上方向に2.5秒間押し続けてから離す
    ```

- `HAT` 定義一覧

  ```
  HAT_UP
  HAT_UP_RIGHT
  HAT_RIGHT
  HAT_DOWN_RIGHT
  HAT_DOWN
  HAT_DOWN_LEFT
  HAT_LEFT
  HAT_UP_LEFT
  HAT_NEUTRAL
  
### スティック

スティックの座標は、128 を基点として 0〜255 の値を指定します。

0・128・255 の 3 つの値は定数定義されているため、置き換えて使用することもできます（0 = STICK_MIN, STICK_NEUTRAL = 128, STICK_MAX = 255）

また、引数にボタンを渡すことでボタンを連打しながらスティックを傾ける操作を行うことができます。

- 左スティックを操作するコマンド

  - `tiltLeftStick(uint8_t lx, uint8_t ly, uint32_t tilt_time, uint16_t button);`

    - lx: 左スティックの x 軸
    - ly: 左スティックの y 軸
    - tilt_time: スティックを傾ける時間の長さ
    - button: 連打するボタン

  - 使用例

    ```
    tiltLeftStick(0, 128, 5000, BUTTON_NONE);                                // 左スティックを左に5秒間倒す
    tiltLeftStick(STICK_NEUTRAL, STICK_MAX, 15000, BUTTON_NONE);           // 左スティックを下に15秒間倒す
    tiltLeftStick(STICK_NEUTRAL, STICK_MIN, 8000, BUTTON_A); // Aボタンを連打しながら、左スティックを上に8秒間倒す
    ```

- 右スティックを操作するコマンド

  - `tiltRightStick(uint8_t rx, uint8_t ry, uint32_t tilt_time, uint16_t button);`

    - rx: 右スティックの x 軸
    - ry: 右スティックの y 軸
    - tilt_time: スティックを傾ける時間の長さ
    - button: 連打するボタン

  - 使用例

    ```
    tiltRightStick(255, 128, 100, BUTTON_NONE);                                 // 右スティックを右に0.1秒間倒す
    tiltRightStick(STICK_MAX, STICK_MIN, 10000, BUTTON_NONE);                 // 右スティックを右上に10秒間倒す
    tiltRightStick(STICK_NEUTRAL, STICK_MAX, 30000, BUTTON_X);  // Xボタンを連打しながら、右スティックを下に30秒間倒す
    ```

- 左右のスティックを同時に操作するコマンド

  - `tiltLeftAndRightStick(uint8_t lx, uint8_t ly, uint8_t rx, uint8_t ry, uint32_t tilt_time, uint16_t button);`

    - lx: 左スティックの x 軸
    - ly: 左スティックの y 軸
    - rx: 右スティックの x 軸
    - ry: 右スティックの y 軸
    - tilt_time: スティックを傾ける時間の長さ
    - button: 連打するボタン

  - 使用例

    ```
    tiltLeftAndRightStick(128, 255, 0, 128, 1000, BUTTON_NONE);                                                // 左スティックを下に、右スティックを左に1秒間倒す
    tiltLeftAndRightStick(STICK_MAX, STICK_MAX, STICK_MIN, STICK_MIN, 30000, BUTTON_NONE);                 // 左スティックを右下に、右スティックは左上に、30秒間倒す
    tiltLeftAndRightStick(STICK_NEUTRAL, STICK_MAX, STICK_MIN, STICK_MAX, 2000, BUTTON_B);   // Bボタンを連打しながら、左スティックを下に、右スティックは左下に、2秒間倒す
    ```

- `STICK` 定義一覧

  ```
  STICK_MIN
  STICK_NEUTRAL
  STICK_MAX

## 参考
[NintendoSwitchControlLibrary](https://github.com/lefmarna/NintendoSwitchControlLibrary)
