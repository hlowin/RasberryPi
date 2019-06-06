## FPGA(Altera DE-0 nano)プロジェクト作成手順

### はじめに
試作品を作るにあたり、先ずはPWMではなくGPIO(5bit幅)で16段階の数値を操作するような制御SWを作成してみる。
下記にシステム概要を示す。

[スマホ]->[Raspberry Pi Zero W]->[Altera DE-0 nano]->7セグメントLED、8ビット幅LED

DE-0 nanoについては5bit幅のデータを受け取り、表示系を駆動させるようなドライバ部として動作。

ドライバ層を作成するにあたり、FPGAプロジェクトを作成する方法について下記に備忘録として残しておく。

### プロジェクトの作成方法
1. Quartus Primeを起動。

2. File -> New Project Wizardを選択。

3. Next

4. 任意のディレクトリを指定(プロジェクトの作成ディレクトリ)/プロジェクト名を入力

5. "Project Type"は"Empty Project"を指定。

6. "Add Files"でソースコード(.v等)を追加。

7. "Family, Device & Board Settings"にて下記を選択。
  - Family : Cyclon IV E
  - Available devices : EP4CE22F17C6

8. あとはデフォルトでよいはず。


## FlashROMへ焼く手順
- [このブログ](https://ehbtj.com/electronics/memo-de0-nano/)を参考。

1. [File]->[Convert Programming Files...]を選択。

2. [Output programming file]->[Programming file type]は[JTAG Indirect Configuration File (.jic)]を選択。

3. [Configuration device]は[EPCS16]を選択。

4. [Input files to convert]->[Flash Loader]を選択。

5. [Add Device...]を選択し、[Cyclone Ⅳ E]->[EP4CE22]を選択->[OK]。

6. [SOF Data]を選択し[Add File...]を選択 -> .sofファイルを選択。

7. [Generate]を選択。

8. Programmerを選択。

9. .sofファイルの項目を右クリックし[Change File]を選択。
   ->選択ウィンドウが出るので、先ほど作成した.jicファイルを選択。

10. EPCS16を選択し、ProgramとVerifyにチェックを入れる。

11. [Start]を選択。