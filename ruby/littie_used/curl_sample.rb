#!/usr/bin/ruby -w
# -*- coding : utf-8 -*-

require 'curl'

#Curl::Easy
#Curl::Multi

http = Curl.get("http://www.google.com/")
puts http.body_str

http = Curl.post("http://www.google.com/",{:foo=>"bar"})
puts http.body_str

http = Curl.get("http://www.google.com/") do |http|
  http.headers['Cookie'] = 'foo=1;bar=2'
end
puts http.body_str

c = Curl::Easy.perfrom("http://www.google.com")
puts c.body_str
c = Curl::Easy.new("http://www.google.com")
c.perform
puts c.body_str
