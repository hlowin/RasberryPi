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