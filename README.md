# CH55xSwitchControl

安価で入手できる中国製マイコンのCH552を使用してNintendo Switchを自動化する為のArduino IDE用ライブラリです。

<img src="https://user-images.githubusercontent.com/21293572/202479479-fff6e791-59a1-463b-bc7a-f67b4cd12cca.jpg" width="50%">

## 必要なもの
**ハードウェア**
- CH552マイコンボード
    - USBシリアル変換機能を搭載したマイコンボードを[Booth](https://bzl.booth.pm/items/4326008)にて販売しています。
- マイコンボードとNintendo Swicthを接続するUSBケーブル

**ソフトウェア**
- Arduino IDE

## 使い方
### 環境設定
**ライブラリのインストール**  
Arduino IDEのライブラリマネージャーの検索窓で本ライブラリ名「CH55xSwitchControl」を検索し、インストールします。


**ch55xduinoのインストール**  
Arduino IDEでCH552マイコンを使用する為に必要となります。
1. ファイル→環境設定を開き、「追加のボードマネージャのURL」に以下のURLを追加してください。
~~~
https://raw.githubusercontent.com/DeqingSun/ch55xduino/ch55xduino/package_ch55xduino_mcs51_index.json
~~~

2. ツール→ボード→ボードマネージャを開き、検索窓で「ch55xduino」を検索し、インストールします。

3. ツール→ボードから、CH552を選択します。

4. ツール→USB Settingsから、「USER CODE w/ 148B USB ram」を選択します。


**入力**  
ライブラリを使いたいファイルの先頭に以下のように記載してください。

~~~
#include <CH55xSwitchControl.h>
~~~

## コマンド一覧

### ボタン

- ボタンを押すコマンド

  - `pushButton(uint16_t button, uint32_t delay_time_msec)`

    - button: 押すボタン
    - delay_time_msec: ボタンを押した後の待ち時間（1 秒 = 1000）
    
  - `pushButtonLoop(uint16_t button, uint32_t delay_time_msec, uint16_t loop_num)`

    - button: 押すボタン
    - delay_time_msec: ボタンを押した後の待ち時間（1 秒 = 1000）
    - loop_num: ボタンを押す回数

  - 使用例

    ```
    pushButton(BUTTON_HOME);        // HOMEボタンを入力する
    pushButton(BUTTON_A, 500);      // Aボタンを入力後、0.5秒待機する
    pushButtonLoop(BUTTON_B, 3000, 10); // 3秒おきにBボタンを入力する、それを10回繰り返す
    ```

- ボタンを長押しするコマンド

  - `pushButtonContinuous(uint16_t button, uint32_t pushing_time_msec)`

    - button: 押し続けるボタン
    - pushing_time_msec: ボタンを押す時間の長さ（1 秒 = 1000）

  - 使用例

    ```
    pushButtonContinuous(BUTTON_L, 2000);       // Lボタンを2秒間押し続けてから離す
    pushButtonContinuous(BUTTON_CAPTURE, 1500); // キャプチャーボタンを1.5秒間押し続けてから離す
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

  - `pushHatButton(uint8_t hat, uint32_t delay_time_msec);`

    - hat: 押す十字キーのボタン
    - delay_time_msec: ボタンを押した後の待ち時間（1 秒 = 1000）

  - `pushHatButtonLoop(uint8_t hat, uint32_t delay_time_msec, uint16_t loop_num);`

    - hat: 押す十字キーのボタン
    - delay_time_msec: ボタンを押した後の待ち時間（1 秒 = 1000）
    - loop_num: ボタンを押す回数
    
  - 使用例

    ```
    pushHatButton(HAT_UP);          // 上キーを1回だけ入力する
    pushHatButton(HAT_LEFT, 1000);  // 左キーを入力後、1秒待機する
    pushHatButtonLoop(HAT_DOWN, 25, 5); // 0.25秒おきに下キーを入力する、それを5回繰り返す
    ```

- 十字キー（方向ボタン）を長押しするコマンド

  - `pushHatButtonContinuous(uint8_t hat, uint32_t pushing_time_msec);`

    - hat: 押し続ける十字キーのボタン
    - pushing_time_msec: ボタンを押す時間の長さ（1 秒 = 1000）

  - 使用例

    ```
    pushHatButtonContinuous(HAT_RIGHT, 5000);   // 右キーを5秒間押し続けてから離す
    pushHatButtonContinuous(HAT_UP_LEFT, 2500); // 十字キーを左上方向に2.5秒間押し続けてから離す
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
  HAT_CENTER
  
### スティック

スティックの座標は、0 を基点として -100〜100 の値を指定します。

- スティックを操作するコマンド

  - `tiltJoystick(uint8_t lx_per, uint8_t ly_per, uint8_t rx_per, uint8_t ry_per, uint32_t tilt_time_msec);`

    - lx_per: LスティックのX方向倒し量
    - ly_per: LスティックのY方向倒し量
    - rx_per: RスティックのX方向倒し量
    - ry_per: RスティックのY方向倒し量
    - tilt_time_msec: スティックを倒し続ける時間

  - 使用例

    ```
    tiltJoystick(-100, 0, 0, 0, 5000);           // Lスティックを左に5秒間倒す
    tiltJoystick(0, 100, 0, 0, 15000);           // Lスティックを下に15秒間倒す
    tiltJoystick(0, 0, 100, 100, 10000);         // Rスティックを右下に10秒間倒す
    ```
