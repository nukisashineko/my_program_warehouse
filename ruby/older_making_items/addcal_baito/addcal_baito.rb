#!/usr/bin/env ruby 
# -*- coding : utf-8 -*-

require 'time'

def main
	if(ARGV.length != 2) 
		puts "usage: <datetime> <duration>"
		return false;
	end
	p datetime = Date.parse(ARGV[0])
	p duration=ARGV[1].gsub(/[^\dh]/,"")
	duration= duration.scan(/\d+/)[0] * 60 if !!duration.match(/h/)
	calender ="XXXXXXXXXXX"
	title = "アルバイト"
	location = "location"
#  datetime = "08/03/2015 10:00"
#	duration="540"
	description=""
	command = "echo '.'| gcalcli --cal %s  add --title '%s'--where '%s' --when '%s' --duration '%s'  --description '%s'"%[calender,title,location,datetime,duration,description]	 

	puts command
#	puts "ok? [y/n]"
#	flag =  !$stdin.gets.chomp.match(/n/)
	flag = true
	system(command) if flag
end


main()

