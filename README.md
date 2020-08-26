# DispChangePlayerPlugin
## 目次

* [概要](#概要)
* [0. BakkesModのインストール](#0-BakkesModのインストール)
* [1. プラグインのダウンロード](#1-プラグインのダウンロード)
* [2. プラグインのインストール](#2-プラグインのインストール)
* [3. プラグインの各項目について](#3-プラグインの各項目について)
* [4. プラグインのアンインストール](#4-プラグインのアンインストール)
* [5. よくある質問](#5-よくある質問)
* [6. コミュニケーション・お問い合わせ先](#6-コミュニケーション・お問い合わせ先)

## 概要
**ロケットリーグ**のMODの1つ、**BakkesMod**のプラグインです。  
プライベートマッチで交代する選手を決め、画面上の表示エリアに名前を表示します。  
交代選手の決定方法は4種から選べます。

1. 試合参加選手から任意の人数分の名前をランダムに表示
2. 各チームの選手から任意の人数分の名前をランダムに表示
3. 各チームにて任意の順位の選手の名前を表示
4. 負けチームにて任意の順位から下位の選手の名前を表示

**※そこそこテストを行ったので問題ないとは思いますが、趣味で作った都合上、ロケットリーグやお使いのPCの保証はいたしかねます。ご利用は自己責任でお願いいたします。何卒、ご了承いただきますようお願い申し上げます。**

## 0. BakkesModのインストール
本プラグインを利用するには、事前に**BakkesMod**をインストールする必要があります。  
インストールの仕方や使い方などは他の方が紹介しているため、ここでは割愛し、参考となるページのみ掲載します。

* [【 ロケットリーグ 】みんな大好き、BakkesMod の使い方](https://note.com/forusian/n/n041bea6cd43f)
* [BakkesModの紹介 Steamのみ](https://note.com/kanrarl/n/nffb6b89f1300)

**BakkesMod**をインストールし、**ロケットリーグ**で動作の確認ができましたら、  
プラグインのダウンロードに進んでください。

## 1. プラグインのダウンロード
下記リンクからプラグインをダウンロードし解凍してください。

[ダウンロード](https://github.com/RLNoNaMe/DispChangePlayerPlugin/archive/master.zip)

たくさんファイルがありますが、  
プラグインのインストールに必要なファイルは下記の2つだけです。

* DispChangePlayerPlugin.dll
* dispchangeplayerplugin.set

解凍したファイル群から2つのファイルが確認できましたら、  
プラグインのインストールに進んでください。

## 2. プラグインのインストール
**BakkesMod**を起動し`File`->`Open BakkesMod folder`をクリックし`bakkesmod`フォルダを開いてください。  
たくさんのフォルダ、ファイルがありますが、  
用があるフォルダは下記の3つだけです。

* `cfg`フォルダ
* `plugins`フォルダ
* `plugins`フォルダ内の`settings`フォルダ

`bakkesmod`フォルダを開きましたら、下記手順に沿ってインストールを行ってください。

1. `cfg`フォルダ内の**plugins.cfg**ファイルを**メモ帳**で開き、「plugin load dispchangeplayerplugin」を追記する
2. `plugins`フォルダ内に、DispChangePlayerPlugin.dllを設置する
3. `plugins`フォルダ内の`settings`フォルダに、dispchangeplayerplugin.setを設置する
4. **ロケットリーグ**を起動する（既に起動している場合は再起動）
5. `F2`キーを押し、**BakkesMod**のメニュー画面を開いて`plugins`タブを押す
6. サイドメニューの**DispChangePlayerPlugin**を押し、操作画面の表示を確認する

これでプラグインのインストールは完了です！  
お疲れさまでした！

## 3. プラグインの各項目について
### Enable
チェックを入れるとプラグインが有効になります。

---

### Random Change Players
試合参加選手から選手名をランダムに表示します。  
表示する選手数は任意に決めれます。  
チェックを入れると有効になります。

### Players Num
試合参加選手から表示する選手数を選択できます。

---

### Random Change Players on Team (Prioritize Random Change Players)
各チームから選手名をランダムに表示します。  
表示する選手数は任意に決めれます。  
チェックを入れると有効になります。  
※`Random Change Players`にチェックが入っている場合はそちらが優先されます。

### Players Num on Team Blue
ブルーチームから表示する選手数を選択できます。

### Players Num on Team Orange
オレンジチームから表示する選手数を選択できます。

---

### Change Players on Team (Prioritize Random Change Players, and Random Change Players on Team)
各チームから任意の順位の選手名を表示します。  
チェックを入れると有効になります。  
※`Random Change Players`、`Random Change Players on Team`のいずれかにチェックが入っている場合はそちらが優先されます。

### Players Rank on Team Blue
ブルーチームから表示する選手の順位を選択できます。

### Players Rank on Team Orange
オレンジチームから表示する選手の順位を選択できます。

---

### Change Low Score Players on Lose Team (Prioritize Random Change Players, Random Change Players on Team, and Change Players on Team)
負けチームにて任意の順位から下位の選手の名前を表示します。  
チェックを入れると有効になります。  
※`Random Change Players`、`Random Change Players on Team`、`Change Players on Team`のいずれかにチェックが入っている場合はそちらが優先されます。

### Low Score Players Num on Lose Team
負けチームから表示する選手の順位を選択できます。  
選択した順位から下位の選手が表示されます。

---

### Fill Box Color
表示エリアの背景色（RGB）、透明度を任意に設定できます。

### Draw Box Color
表示エリアの枠の色（RGB）、透明度を任意に設定できます。

### Box Position
表示エリアの表示位置を任意に設定できます。

### Box Scale
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
本プラグインのバグが原因かもしれません。  
本プラグインをアンインストールし、**ロケットリーグ**をプレイしてみてください。  
それでもダウンするようでしたら、多分、原因は別にあります。
解決しないようであれば、大変申し訳ございませんが、**ロケットリーグ**の再インストールをお願いします。

### 5.2. 日本語の選手名が「???????」と表示される
できれば日本語対応したかったのですが、  
恐らく**Bakkesmod**側が対応していないため、残念ながら難しそうです。  
文字数は据え置きなのでそこで判断していただくか、  
同文字数ならスコアが低い人を交代とするなど、使用者の裁量にお任せいたします...

### 5.3. カジュアル、ランクでもこのプラグインが動いているけどBANされない？
本プラグインは、**Bakkesmod**が**ロケットリーグ**から取得しているデータを、  
試合終了後にこねくり回しているだけなので、  
**Bakkesmod**が直接サーバで操作していない限り、大丈夫だと思われます。  
ただ現状確証を得ていないため、不安でしたら`Enable`のチェックを外し、  
本プラグインを無効にしておくことをオススメいたします。

### 5.4. 今後のアップデート予定は？
下記アップデートを予定してます。

* 文字色の任意変更
* 表示エリアの大きさを任意に設定
* デザインに自由度を持たせるためOBSとの連携

予定はしてますが、趣味で作っている都合上、
いつごろ完成するかはわかりませんし、完成を約束できません。  
首を長くして待っていいただけますと幸いです。

### 5.5. 他にプラグインを作る予定はある？
今のところないです。  
いいアイディアとやる気が沸いてきたら作るかもしれません。  
リクエストも受け付けておりません。ごめんね。

## 6. コミュニケーション・お問い合わせ先

| Name | Comment |
| :---: | :--- |
| [Twitter](https://twitter.com/azurehawk)| あんまりつぶやかないです。 |
| [Discord](https://discord.gg/bk6cWFU)| ライブとかするかもです。仲良くしてね！ |
