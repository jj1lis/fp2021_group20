# fp2021_group20
電気通信大学2021年度「基礎プログラミングおよび実習」、第15回で編成されたグループ20のためのレポジトリです。

# 成果物
![animation](https://github.com/jj1lis/fp2021_group20/blob/main/fireworks.gif)

## ここって？
"GitHub"というソフトウェア開発プラットフォームの、レポジトリと呼ばれるデータとか何やらを置いてある場所です。
特に興味があるのでなければ、詳しいことを気にする必要はありません。

### 使い方
[`src`](https://github.com/jj1lis/fp2021_group20/tree/main/src) にソースコードが置いてあります。
とりあえず教科書の内容+アルファをそのまま書いたソースコードに、各所でどういう処理をしているのかを説明するコメントをつけておきました。分からなくなったら参照してください。

作成したプログラムをLINEでもメールでもいいので送りつけて貰えれば僕がテストしてマージします。
当然ここに直接PRを送ってくれても大丈夫です！！

# コーディングのルール
複数人で開発する場合、プログラムは自分だけが読めればいいわけではありません。他人が読んで意味の分かるよう、次の規則に従ってコーディングを行いましょう。

## 自分の担当処理は自分のソースコードで完結させる
他人のプログラムにまで影響を与えるような変更をすると、プロジェクト全体がしっちゃかめっちゃかになります。
設計と分担に従って、要求された機能を満たすものを過不足なく実装しましょう。

## ヘッダファイルを書く
他の箇所で使われる関数の宣言はまとめてヘッダファイルにしてください。

ソースファイルが`hoge.c`なら、ヘッダのファイル名は`hoge.h`でお願いします。

## 変数名や関数名は意味のあるものにする
例えば支払う金額を記憶する変数を作るとき、その名前を`a`とか`b`とか、`ああああ`とつけるのは賢い方法ではありません。`money`とするだけでも理解のきっかけになりますし、`payment`と書けば完璧です。

## 何をしているのかコメントに書く
コメントのないコードを読むことは暗号解読に近いです。

```
for(i = 0; i < width; i++) {
  for(j = 0; j < height; j++) {
    img_putpixel(c, x_min + i, y_min + j);
  }
}
```

次のようにコメントをつけるだけでも、他の人が処理の内容を理解する助けになります：大抵の場合、読む人は「何がしたいの？」さえ知ることができればいいわけですから。
```
// 点(x_min, y_min)から右へ幅width、下へ高さheightの長方形を色cで塗りつぶす
for(i = 0; i < width; i++) {
  for(j = 0; j < height; j++) {
    img_putpixel(c, x_min + i, y_min + j);
  }
}
```
