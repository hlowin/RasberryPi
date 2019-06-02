## 7セグメントLEDカウントアップ作成

### ことはじめ
そもそもRasberry Pi Zeroにはフラッシュメモリのアクセス状態を表示するLED以外にLEDついていなさそうなので、自前で用意した7セグLEDをカウントアップさせる。

### Pin Assignment
- PINアサインが分からんのだなあ…
  [Raspberry Pi Zeroについて](http://hara.jpn.com/_default/ja/Topics/RaspPiZero.html)という記事に書いてあった。

### 環境
PINアサインを見る限り、自作したFPGA接続用の7セグメントLED基盤をそのまま流用することは難しそうなので、下記の様に接続することにする。

- [Rasberry Pi Zero WH] -> (4Pin GPIO出力) -> [Altera DE-0 nano] -> [7セグメントLED] 

  - Windows 10 Home 1809
  - Rasberry Pi Zero WH
  - Transcend Micro SD HC Class6
  - Altera DE-0 nano(FPGA)
  - W1-391ABB(7セグメントLED)
  - 898-3-R180(グループ抵抗)

### SSH接続が出来なくなってしまった件について
LEDの作業をやっている際に、何回かRassbery PiとPCと接続しているUSBを抜き差ししてしまった。
ファイルもしくはOSをクラッシュさせてしまったかと思ったが、USBケーブルを交換してみたところ直った。

<pre/>
当たり前だが、デバイスマネージャ上に"USB Ethernet/RNDIS Gadget"が表示されているとSSH接続できる。
</pre>

### ライブラリ
~~GPIOを制御するためにレジスタ直叩きでもよいと思われるが、今回は簡単にその処理をwrappしているAPIを使用して制御させたいと思う。~~

~~今回はArduinoライクなAPIらしい"WiringPi"を使用してみる。~~ 

~~下記コマンドでWiringPiをインストールする。~~

~~sudo pip install wiringpi2~~


### GPIOレジスタ
やっぱりレジスタ直叩きでやってみるか…
[この記事](https://qiita.com/moutend/items/534d597cf5c867273319)を参考。

マイコンマニュアルを見てみる。
"6.1 Register View"に書いている内容としては、0x7E20 0000～0x7E20 00B0までがGPIOを制御するためのレジスタ。
アドレスが1増える当たり8bit増える、アドレス辺りのデータは32bit幅。


# LEDチカチカ
[この記事](https://qiita.com/moutend/items/534d597cf5c867273319)通りにGPIO23を使用。

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


### GPIOピン番号
[この記事](https://qiita.com/moutend/items/534d597cf5c867273319)を参考。
上側がmicroSD側。

```
        +3V3 1  2   +5V
GPIO2   SDA1 3  4   +5V
GPIO3   SCL1 5  6   GND
GPIO4   GCLK 7  8   TXD0  GPIO14
         GND 9  10  RXD0  GPIO15
GPIO17  GEN0 11 12  GEN1  GPIO18
GPIO27  GEN2 13 14  GND
GPIO22  GEN3 15 16  GEN4  GPIO23
        +3V3 17 18  GEN5  GPIO24
GPIO10  MOSI 19 20  GND
GPIO9   MISO 21 22  GEN6  GPIO25
GPIO11  SCLK 23 24  CE0_N GPIO8
         GND 25 26  CE1_N GPIO7
EEPROM ID_SD 27 28  ID_SC EEPROM
GPIO5        29 30  GND
GPIO6        31 32        GPIO12
GPIO13       33 34  GND
GPIO19       35 36        GPIO16
GPIO26       37 38        GPIO20
         GND 39 40        GPIO21
```

### LEDカウントアップ
試作品(はんだ付けめっちゃ汚い)の都合で、GPIO21をOUTPORTで使用。

"/dev/mem"はroot権限が必要となるため、"/dev/gpiomem"を使用する。