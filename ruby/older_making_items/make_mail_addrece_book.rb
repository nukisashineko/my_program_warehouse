#!/bin/sh
exec ruby -x "$0" "$@"
#!ruby
# -*- coding : utf-8 -*-
require 'date'
require 'scanf'
def make_vcard (name="",sort_name="",phonenumber="",email_addrece="")
name||=""
sort_name||=""
phonenumber||=""
email_addrece||=""
'BEGIN:VCARD
VERSION:3.0
FN:'+name+'
N:'+name+';;;;
SORT-STRING:'+sort_name+'
TEL;TYPE=PREF,CELL:'+phonenumber+'
EMAIL;TYPE=PREF,CELL:'+email_addrece+'
X-GNO:0
X-GN:
X-REDUCTION:0
CLASS:PUBLIC
REV:'+Time.now.strftime("%Y%m%dT%H%M%SZ")+'
END:VCARD
'
end

def read_addrece_number(filename)
	File.open(filename,'r') do |f|
		f.each_line do |l|
			name,sort,phone=l.scanf("%s %s %s")
			print make_vcard(name,sort,phone)
		end
	end
end
#=======main=========
puts "load from "+ARGV[0]

read_addrece_number(ARGV[0])
#==============
