# DispChangePlayerPlugin
## 概要
ロケットリーグのMODの1つ、BakkesModのプラグインです。  
プライベートマッチで交代する選手を決め、画面上の表示エリアに名前を表示します。  
交代選手の決定方法は4種から選べます。

1. 試合参加者から任意の人数をランダムに決定
2. 各チームから任意の人数をランダムに決定
3. 各チームにて任意の順位から下位
4. 負けチームにて任意の順位から下位


## 0. BakkesModのインストール
本プログラムはBakkesModのプラグインです。  
本プログラムを利用するには、事前にBakkesModをインストールする必要があります。  
インストールの仕方や使い方などは他の方が紹介しているため、ここでは割愛し、参考となるページのみ掲載します。

* [【 ロケットリーグ 】みんな大好き、BakkesMod の使い方](https://note.com/forusian/n/n041bea6cd43f)
* [BakkesModの紹介 Steamのみ](https://note.com/kanrarl/n/nffb6b89f1300)

BakkesModをインストールし、ロケットリーグで動作の確認ができましたら、  
プラグインのダウンロードに進んでください。

## 1. プラグインのダウンロード方法
本ページ上部の緑色のCodeボタン→Download ZIPボタンから、  
もしくは下記リンクからプラグインをダウンロードし解凍してください。

[ダウンロード](https://github.com/RLNoNaMe/DispChangePlayerPlugin/archive/master.zip)

プラグインのインストールに必要なファイルは2つだけです。

1. DispChangePlayerPlugin.dll（`plugins`フォルダ内）
2. dispchangeplayerplugin.set（`plugins`フォルダ->`setting`フォルダ内）

解凍したファイル群から2つのファイルが確認できましたら、  
プラグインのインストールに進んでください。

## 2. プラグインのインストール方法
下記手順に沿ってインストールを行ってください。

1. BakkesModを起動し`File`->`Open BakkesMod folder`でフォルダを開く
2. `plugins`フォルダを開き、DispChangePlayerPlugin.dllファイルを設置する
3. `settings`フォルダを開き、dispchangeplayerplugin.setファイルを設置する
4. BakkesModを起動し`File`->`Open BakkesMod folder`でフォルダを開く
5. `cfg`フォルダのplugins.cfgをメモ帳で開き「plugin load dispchangeplayerplugin」を追記する
6. ロケットリーグを起動する（既に起動している場合は再起動）

F2キーを押し、BakkesModのメニュー画面を開いて`plugins`タブを押し、  
サイドメニューに「DispChangePlayerPlugin」が追加されていることが確認できましたら、  
プラグインのインストール完了です。


## 3. プラグインの操作方法
### 3.1. プラグインの操作画面の表示
1. F2キーを押しBakkesModのメニュー画面を開く
2. `plugins`タブを押し、左のサイドメニューから「DispChangePlayerPlugin」を選択

### 3.2. 操作画面の説明
#### Enable
プラグインのオン・オフ

#### Random Change Players

#### Players Num

#### Random Change Players on Team (Prioritize Random Change Players)

#### Players Num on Team Blue

#### Players Num on Team Orange

#### Change Players on Team (Prioritize Random Change Players, and Random Change Players on Team)

#### Players Rank on Team Blue

#### Players Rank on Team Orange

#### Change Low Score Players on Lose Team (Prioritize Random Change Players, Random Change Players on Team, and Change Players on Team)

#### Low Score Players Num on Lose Team

#### Fill Box Color

#### Draw Box Color


