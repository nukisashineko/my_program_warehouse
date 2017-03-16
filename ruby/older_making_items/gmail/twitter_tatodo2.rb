
# -*- coding : utf-8 -*-
require 'twitter'
require 'pp'


client = Twitter::REST::Client.new do |config|
  config.consumer_key = 'XXXXXXXXXXXXXXXXXXXXXX'
  config.consumer_secret = 'XXXXXXXXXXXXXXXXXXXXXX'
  config.access_token = 'XXXXXXXXXXXXXXXXXXXXXX'
  config.access_token_secret = 'XXXXXXXXXXXXXXXXXXXXXX'
end

def collect_with_max_id(collection=[], max_id=nil, &block)
  response = yield max_id
  collection << response
  response.empty? ? collection.flatten : collect_with_max_id(collection, response.last.id - 1, &block)
end

def get_all_tweets(client,user)
  collect_with_max_id do |max_id|
    options = {:count => 200, :include_rts => true}
    options[:max_id] = max_id unless max_id.nil?
    client.user_timeline(user, options)
  end
end

 get_all_tweets(client,"tatodo2").each {|x| printf "%s : %s",Twitter.user?(x.id),x.text}

#自分のタイムラインの取得
pp client.home_timeline

client.search("#ruby -rt",:lang =>"ja").take(5).collect do |tweet|
"#{tweet.user.screen_name}:  #{tweet.text}"
 end


#自分宛てのReplyの取得
# pp Twitter.mentions
#自分宛てのDMの取得
pp client.direct_messages
#発言する
def tatodo2_tweet(text)
  client.update (text)
end
