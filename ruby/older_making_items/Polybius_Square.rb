#!/bin/sh
exec ruby -x "$0" "$@"
#!ruby
# -*- coding : utf-8 -*-



temp=("a".."z").map {|c| c}

encode_table={}
decode_table={}
i=0


temp.delete("j")
decode_table["24"]="j"
encode_table["j"]="24"
temp.each do |c|
 number=(i%5+1)*10+(i/5+1)
 decode_table[number.to_s]=c
 encode_table[c]=number.to_s
 i+=1
end

puts "encode is "+ARGV[0].split("").map{|c| encode_table[c]}.join('').to_s
puts "decode is "+ARGV[0].scan(/.{1,2}/).map{|num| decode_table[num]}.join('').to_s
