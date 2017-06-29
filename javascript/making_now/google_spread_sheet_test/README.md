```
mv XXXXXXXXXX-1111111111111.json google-generated-creds.json
```


シート１の内容はいかにしたら動く
要するに１つオフセット取りながら１行と
５行取得の時にエラー博からそれの回避が書いてないからデータを７行くらい用意しておけばいいって話。
```
1	2	3
1	2	3
7	8	9
10	11	12
13	14	15
16	17	18
16	17	18
```


資料：
- [node-google-spreadsheetを使う(超簡易的なテスト) - Qiita](http://qiita.com/daikiojm/items/b7998c94b174f474d13f)
    - header的に拾うなら使うかも？（使わない）
- [google-spreadsheet](https://www.npmjs.com/package/google-spreadsheet)
     - 本家ライブラリ。見本のやつをhelloworld.jsに書き込んだが、save,bulkUpdateCellsなどでcallbackがついていなくて落ちるバグがある。helloworld.jsでは、明示的にcallbackを付けて握りつぶしている。
- [PythonからOAuth2.0を利用してスプレッドシートにアクセスする - Qiita](http://qiita.com/koyopro/items/d8d56f69f863f07e9378)
     - googleのOAuth2.0 keyの発行が画像付きでわかりやすい。UIは微妙に変わっている点とかに注意。
     - 認証情報でサービスアカウントを作成するとダウンロードされるJSONファイルはgoogle-generated-creds.jsonにrenameしてこのフォルダに置くこと。
- [googlespreadsheet\_bot\_test - Google スプレッドシート](https://docs.google.com/spreadsheets/d/1F-qvqxw2W5WvB_UZMVZGPb3YqY7o1yefr5E98AARWxo/edit#gid=0)
     - とりあえずbotテスト用に作ったspreadsheetのURL（非公開）。
     - google-generated-creds.jsonに書いてあるclient-emailをシートの共有者に指定すればどのシートでも使えるので自分のシートで作ってためそう。
- [アルバイト勤怠表（大澤） - Google スプレッドシート](https://docs.google.com/spreadsheets/d/1BVXxhHYfeSLYE4eTFtdvmlRqTK62OIYbPI7hJq9y48g/edit#gid=1401117683)
     - 本番環境なので一応書いておく
- [How to find your Google Spreadsheet Key](http://www.coolheadtech.com/blog/use-data-from-other-google-spreadsheets)
     - helloworld.jsでスプレットシートのIDを指定しているが、URLに含まれているハッシュがキーであるためそれを書く。
