#!/usr/bin/ruby -w
# -*- coding : utf-8 -*-
user = "<gmail user>"
pass = "<gmail pass>"

require './gmail_func'

#main start
while(1)
gmail_func(user,pass)
puts "sleep 100s..."
sleep 100
end
#main end
