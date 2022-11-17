# CH55xSwitchControl

中国製マイコンのCH552を使用してNintendo Switchを自動化する為のArduino IDE用ライブラリです。
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
