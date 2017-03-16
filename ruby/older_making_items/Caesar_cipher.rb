#!/bin/sh
echo "$@"
exec ruby -x "$0" "$@"
#!ruby
# -*- coding : utf-8 -*-

if ARGV[0]==nil
 puts "Usage : #{$0} <string>"
 exit
end

temp=ARGV
temp.inject(:+)

27.times do
temp=temp.map do |t|
 t.split(//).map{|c| c.next[0]}.join 
end
p temp.join(' ')
end
