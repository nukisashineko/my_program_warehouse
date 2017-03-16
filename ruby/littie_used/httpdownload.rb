#!/usr/bin/ruby -w
# -*- coding : utf-8 -*-

require 'httpclient'

hc = HTTPClient.new
hoge_doc = hc.get_content('http://www.hogehoge.com/hoge.html',:get,{})
p hoge_doc
