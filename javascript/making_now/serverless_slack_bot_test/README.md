とりあえず、helloworldを返すlambda botの作成


参考:
- [SlackのWebhook URL取得手順 - Qiita](http://qiita.com/vmmhypervisor/items/18c99624a84df8b31008)
    - こっちがWebHookでHelloWorldするために利用した記事
- [Building a serverless chatbot on AWS Lambda](https://www.blackpepper.co.uk/blog/creating-a-serverless-slack-bot-on-aws-lambda)
    - こっちやろうとして無理だったから、その中のlocal.ymlのやり方だけ真似たが今は必要ない。


`sls create --template aws-nodejs`を使って関数作ったらその返り値を`{text:"XXXXX"}`に変更する。
serverless.ymlの中身をPOSTに変更して
outgoing-webhooksを作って、その設定のURLにデプロイ後のhello functionのURLをぶち込む。
するとhelloが帰ってくる。
webhooks設定で単語を指定しないとBOT自身のレスに反応して無限ループするので注意。



```local.yml
dev:
  slack:
    clientId: XXXXXXXXXXXXXXXXXXXXXXXXXXXX
    clientSecret: 11111111111.22222222222

production:
  slack:
    clientId: XXXXXXXXXXXXXXXXXXXXXXXXXXXX
    clientSecret: 11111111111.22222222222
```