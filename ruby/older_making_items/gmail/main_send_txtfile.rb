#!/usr/bin/ruby -w
# -*- coding : utf-8 -*-
user = "<gmail user>"
pass = "<gmail pass>"

require './gmail_func'

def usage
puts "\
  argment error ... \n\
  Usage: #{File.basename $0} <string>"
exit
end

#main start
usage unless ARGV.length ==1
puts "filename is "+ARGV[0]+" open...."
body = File.read(ARGV[0])
bodys = split_text(body)

Gmail.new(user,pass) do |gmail|
  send_bodys(
	gmail,
	to_addr = "amazyaku.is.fish0danya-@ezweb.ne.jp",
	url = ARGV[0],
	bodys
)
end
#main end
