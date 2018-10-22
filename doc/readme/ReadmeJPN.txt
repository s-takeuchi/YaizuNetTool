=================================================
StkFw 1.6.0
=================================================
1.StkFw概要

StkFwは，「複数のソフトウェア／ハードウェアがIPネットワーク上で連携し
て動作する環境」をシミュレートするテスト支援ソフトウェアです。
ネットワーク上の複雑で高価な要素（ソフトウェアやハードウェア）と相互接続／
連携して動作するソフトウェアの開発で，各要素の振る舞いをテストプログラム化
することにより開発対象ソフトウェアのテスト工数を削減する手法は一般に良く
知られています。
しかし，テストプログラムの振る舞い（他ネットワーク要素との遣り取り）が複雑
な場合，テストプログラム開発のための初期投資費用が高くなる場合があります。

StkFwは，優れたユーザーインターフェースにより，IPネットワーク上での
データの送受信を簡易且つ詳細に制御できます。これにより実際にテストプログラム
を開発しなくても，テストプログラムと同等の振る舞いをStkFwで実現する
ことができ，ソフトウェアのテストに関わる工数を低減することができます。


=================================================
2.システム要件

StkFwは以下の環境で動作します。

動作に必要なCPU:
1GHz以上のクロック周波数で動作するCPU

動作に必要なメモリ容量:
512MBytes以上

導入に必要な空きディスク容量:
20MBytes以上

サポートするオペレーティングシステム／エディション:
Windows 7 Professional/Ultimate SP1
Windows 8 Pro
Windows 8.1 Pro
Windows 10 Pro
Windows Server 2008 R2 Standard
Windows Server 2012 Standard
Windows Server 2012 R2 Standard 


=================================================
3.変更履歴
* バージョン 1.0.0 ---> 1.1.0
(1) リポジトリデータをセーブ／ロードしたフォルダが，StkFw再起動後の初期
    フォルダに設定される不具合を修正した。
(2) アイコン名の表示がアイコンの中心からずれる不具合を修正した。
(3) 本ソフトウェアの目的をテスト・フレームワークからテスト支援ソフト
    ウェアに変更した。
(4) ループバックネットワークアダプタ追加／削除ダイアログをサポートした。
(5) OS再起動後に追加/削除したIPアドレスがもとにもどるIPアドレスウィザード
    の不具合を修正した。
(6) 変数管理機能(Variable Controller)をサポートした。

* バージョン 1.1.0 ---> 1.2.0
(1) Administratorsグループに属さないユーザーがStkFwを使用できるようにした。
(2) スレッドコントローラで通信ログ出力機能をサポートした。
(3) Windows 7, Windows Server 2003, Windows Server 2008をサポートした。
(4) 複数のメインコンソールを同時に起動できるようにした。
(5) バックグラウンドプロセスとしてスレッドを実行する機能をサポートした。
(6) 複数の変数のエクスポート／インポートをサポートした。
(7) 複数のスレッドが1つのスレッドに連結するデータフローで，データフローの
    終端となる処理要素に処理が到達しても，一部のスレッドの処理が完了しない
    不具合を修正した。
(8) 複数のスレッドが1つのスレッドに連結するデータフローで，データが不正に
    上書きされたり，余分に処理される不具合を修正した。

* バージョン 1.2.0 ---> 1.3.0
(1) ファイルへの書き込みおよびファイルからの読み込みを行う処理要素をサポート
    した。
(2) 外部プログラムを実行する処理要素をサポートした。
(3) 全スレッド一括開始／停止機能をサポートした。
(4) TCP receiverの終了条件を指定できるようにした。新たにデータ長超え検知と
    データ一致検知を終了条件として追加した。

* バージョン 1.3.0 ---> 1.4.0
(1) 強制クローズと接続先のシャットダウン検知によるクローズの2つのソケット
    クローズ方法をサポートした。
(2) ワークスペースサイズを変更できるようにした。
(3) 処理要素の追加に関する階層化されたメニューを提供した。
(4) UDP receiver処理要素およびUDP sender処理要素を新たにサポートした。
(5) ソケットクローズ時に誤った処理要素のIDがログに出力される不良を対策した。
(6) Windows 8, Windows Server 2012, Windows Server 2003 R2, 
    Windows Server 2008 R2をサポートした。

* バージョン 1.4.0 ---> 1.5.0
(1) インストーラプログラム（ファイル）をひとつのMSIファイルに統合した。
(2) 同一ポートで複数クライアントからの同時接続を可能にした。
(3) スレッド停止時に同じ受信要素が冗長なソケットクローズのログを出力する不良
    を対策した。
(4) /openまたは/startパラメータ指定で起動したときに，カレントフォルダが.std
    ファイルが配置されたフォルダと異なる不良を対策した。
(5) IPv6による接続をサポートした。
(6) Windows 8.1, Windows 10, Windows Server 2012 R2をサポートした。

* バージョン 1.5.0 ---> 1.6.0
(1) TCP receiverの終了条件として，HTTPヘッダのContent-Lengthに指定されたサイ
    ズのデータ受信を新たにサポートした。
(2) HTTPヘッダの追加および削除を可能にする処理要素を新たにサポートした。

=================================================
4.使用許諾条件

The MIT License (MIT)

Copyright (c) 2018 Shinya Takeuchi

Permission is hereby granted, free of charge, to any person obtaining a copy
of this software and associated documentation files (the "Software"), to deal
in the Software without restriction, including without limitation the rights
to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
copies of the Software, and to permit persons to whom the Software is
furnished to do so, subject to the following conditions:

The above copyright notice and this permission notice shall be included in all
copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
SOFTWARE.


=================================================
5.インストール方法

stkfw.msiを実行することによりインストーラが起動します。
インストーラの指示に従いインストールを進めてください。


=================================================
6.問い合わせ先

URL: https://github.com/s-takeuchi/
本ソフトウェアに関する問い合わせは，下記メールアドレスで受け付けています。

bamboo@rj.dream.jp
竹内伸也　（たけうちしんや）

