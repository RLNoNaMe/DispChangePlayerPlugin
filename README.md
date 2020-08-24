# DispChangePlayerPlugin
## 概要
ロケットリーグのMODの1つ、BakkesModのプラグインです。  
プライベートマッチで交代する選手を決め、画面上の表示エリアに名前を表示します。  
交代選手の決定方法は4種から選べます。

1. 試合参加選手から任意の人数分の名前をランダムに表示
2. 各チームの選手から任意の人数分の名前をランダムに表示
3. 各チームにて任意の順位から下位の選手の名前を表示
4. 負けチームにて任意の順位から下位の選手の名前を表示

※趣味で作成したものなので、プラグインインストール後のロケットリーグの動作保証はいたしかねます。

## 0. BakkesModのインストール
本プログラムはBakkesModのプラグインです。  
本プログラムを利用するには、事前にBakkesModをインストールする必要があります。  
インストールの仕方や使い方などは他の方が紹介しているため、ここでは割愛し、参考となるページのみ掲載します。

* [【 ロケットリーグ 】みんな大好き、BakkesMod の使い方](https://note.com/forusian/n/n041bea6cd43f)
* [BakkesModの紹介 Steamのみ](https://note.com/kanrarl/n/nffb6b89f1300)

BakkesModをインストールし、ロケットリーグで動作の確認ができましたら、  
プラグインのダウンロードに進んでください。

## 1. プラグインのダウンロード
本ページ上部の緑色のCodeボタン→Download ZIPボタンから、  
もしくは下記リンクからプラグインをダウンロードし解凍してください。

[ダウンロード](https://github.com/RLNoNaMe/DispChangePlayerPlugin/archive/master.zip)

いろいろなファイルがありますが、  
プラグインのインストールに必要なファイルは下記の2つだけです。

1. DispChangePlayerPlugin.dll（`plugins`フォルダ内）
2. dispchangeplayerplugin.set（`plugins`フォルダ->`setting`フォルダ内）

解凍したファイル群から2つのファイルが確認できましたら、  
プラグインのインストールに進んでください。

## 2. プラグインのインストール
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
#### __Enable__
チェックを入れるとプラグインが有効になります。

---

#### __Random Change Players__
試合参加選手から選手名をランダムに表示します。  
表示する選手数は任意に決めれます。  
チェックを入れると有効になります。

#### __Players Num__
試合参加選手から表示する選手数を選択できます。

---

#### __Random Change Players on Team (Prioritize Random Change Players)__
各チームから選手名をランダムに表示します。  
表示する選手数は任意に決めれます。  
チェックを入れると有効になります。  
※`Random Change Players`にチェックが入っている場合は無効になります。

#### __Players Num on Team Blue__
ブルーチームから表示する選手数を選択できます。

#### __Players Num on Team Orange__
オレンジチームから表示する選手数を選択できます。

---

#### __Change Players on Team (Prioritize Random Change Players, and Random Change Players on Team)__
各チームから任意の順位の選手名を表示します。  
チェックを入れると有効になります。  
※`Random Change Players`、または`Random Change Players on Team`にチェックが入っている場合は無効になります。

#### __Players Rank on Team Blue__
ブルーチームから表示する選手の順位を選択できます。

#### __Players Rank on Team Orange__
オレンジチームから表示する選手の順位を選択できます。

---

#### __Change Low Score Players on Lose Team (Prioritize Random Change Players, Random Change Players on Team, and Change Players on Team)__
負けチームにて任意の順位から下位の選手の名前を表示します。  
チェックを入れると有効になります。  
※`Random Change Players`、`Random Change Players on Team`、または`Change Players on Team`にチェックが入っている場合は無効になります。

#### __Low Score Players Num on Lose Team__
負けチームから表示する選手の順位を選択できます。  
選択した順位から下位の選手が表示されます。

---

#### __Fill Box Color__
表示エリアの背景色（RGB）、透明度を任意に設定できます。

#### __Draw Box Color__
表示エリアの枠の色（RGB）、透明度を任意に設定できます。

#### __Box Position__
表示エリアの表示位置を任意に設定できます。

#### __Box Scale__
表示エリアの大きさを正常に設定できません。今後修正予定です。


## 4. プラグインのアンインストール
アンインストールは下記の手順で行えます。

1. BakkesModを起動し`File`->`Open BakkesMod folder`でフォルダを開く
2. `plugins`フォルダを開き、DispChangePlayerPlugin.dllファイルを削除する
3. `settings`フォルダを開き、dispchangeplayerplugin.setファイルを削除する
4. BakkesModを起動し`File`->`Open BakkesMod folder`でフォルダを開く
5. `cfg`フォルダのplugins.cfgをメモ帳で開き「plugin load dispchangeplayerplugin」の記載を削除する

## 5. よくある質問
### 5.1. 試合終了と同時にロケットリーグがダウンする
本プラグインのバグかもしれません。  
一度本プラグインをアンインストールし、ロケットリーグをプレイしてみてください。  
それでもダウンするようでしたら多分、原因は別にあります。
解決しないようであればロケットリーグの再インストールをお願いします。

### 5.2. 今後のアップデート予定は？
下記アップデートを予定してます。

* 文字色の任意変更
* 表示エリアの大きさを任意に設定
* デザインに自由度を持たせるためOBSとの連携

予定はしてますが、趣味で作っているものなのでいつごろ完成するかはわかりません。  
首を長くして待っていいただけますと幸いです。

### 5.3. 他にプラグインを作る予定はある？
今のところないです。  
いいアイディアとやる気が沸いてきたら作るかもしれません。  
リクエストも受け付けておりません。ごめんね。

## 6. コミュニケーション

| Name | Comment |
| :---: | :--- |
| [Twitter](https://twitter.com/azurehawk)| あんまりつぶやかないです。 |
| [Discord](https://discord.gg/bk6cWFU)| ライブとかするかもです。仲良くしてね！ |
