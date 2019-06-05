## Blynkインストール&実行

### ことはじめ
プラレールソリューションを作成するに当たり、先ずは7セグLEDの値をリモコンから変化させられる様にしたい。

そのために、先ずは"Blynk"ライブラリのインストールを行う。

[このブログ](https://homemadegarbage.com/raspi0w-01)を参考にインストール。


### インストール手順

1. Blynkライブラリのクローン

  ```
  $ git clone https://github.com/blynkkk/blynk-library.git
  ```

2. WiringPiのインストール

  ```
  $ sudo apt-get install wiringpi
  ```

  - 一応これでライブラリ導入は完了。

