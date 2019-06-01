## 7セグメントLEDカウントアップ作成

### ことはじめ
そもそもRasberry Pi Zeroにはフラッシュメモリのアクセス状態を表示するLED以外にLEDついていなさそうなので、自前で用意した7セグLEDをカウントアップさせる。

### Pin Assignment
- PINアサインが分からんのだなあ…
  [Raspberry Pi Zeroについて](http://hara.jpn.com/_default/ja/Topics/RaspPiZero.html)という記事に書いてあった。

### 環境
PINアサインを見る限り、自作したFPGA接続用の7セグメントLED基盤をそのまま流用することは難しそうなので、下記の様に接続することにする。

- [PC] -> (ソースコードダウンロード) -> [Rasberry Pi Zero WH] -> (4Pin GPIO出力) -> [Altera DE-0 nano] -> [7セグメントLED] 

  - Windows 10 Home 1809
  - Rasberry Pi Zero WH
  - Transcend Micro SD HC Class6
  - Altera DE-0 nano(FPGA)
  - W1-391ABB(7セグメントLED)
  - 898-3-R180(グループ抵抗)

### SSH接続が出来なくなってしまった件について
LEDの作業をやっている際に、何回かRassbery PiとPCと接続しているUSBを抜き差ししてしまった。
ファイルもしくはOSをクラッシュさせてしまったかと思ったが、USBケーブルを交換してみたところ直った。

- 当たり前だが、デバイスマネージャ上に"USB Ethernet/RNDIS Gadget #2"が表示されているとSSH接続できる。

### ライブラリ
~~GPIOを制御するためにレジスタ直叩きでもよいと思われるが、今回は簡単にその処理をwrappしているAPIを使用して制御させたいと思う。~~

~~今回はArduinoライクなAPIらしい"WiringPi"を使用してみる。~~ 

~~下記コマンドでWiringPiをインストールする。~~

```
sudo pip install wiringpi2
```

やっぱりレジスタ直叩きでやってみるか…
[この記事](https://qiita.com/moutend/items/534d597cf5c867273319)を参考。

マイコンマニュアルを見てみる。
"6.1 Register View"に書いている内容としては、0x 7E20 0000～0x 7E20 0014までがGPIOを制御するためのレジスタ。

大体上記の記事と同じ内容だったため、内容の記載はパス。

一先ず、記事内のサンプルコードを転送してビルドしてみる。

```
% gcc -c blink.c
% gcc main.c blink.o -o ./blinkLED
```

"blink.h"の中身について一行変更する。
```c
// #define PERIPHERAL_BASE 0x3F000000 // For Rasberry Pi 2
#define PERIPHERAL_BASE 0x20000000    // For Rasberry Pi Zero
```
Pi 2とZeroでペリフェラルのベースアドレスが異なるぽい。
[このブログ](http://hp.vector.co.jp/authors/VA011973/raspberrypi_1.htm)を参考。