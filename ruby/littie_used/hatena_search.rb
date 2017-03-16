#!/usr/bin/ruby -w
# -*- coding : utf-8 -*-


require 'net/http'

Net::HTTP.version_1_2

Net::HTTP.start('www.hatena.ne.jp',80){|http|
  response = http.post('/o/search/top',"get=ruby")
  puts response.body

}
