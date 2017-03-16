#!/usr/bin/ruby -w
# -*- coding : utf-8 -*-

require 'net/http'


http =Net::HTTP.new('www.ruby-lang.org',80)
http.open_timeout = 10
http.read_timeout = 60
http.start do 
  response =http.get('/ja/')
  puts response.body
end

