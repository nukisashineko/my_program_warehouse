#!/usr/bin/ruby 
# -*- coding : utf-8 -*-

filename=".temp_to_nextfile"


unless File::exists? filename  then
 puts 'file not exists '+filename
 File.open(filename,"w"){|f| f.print `ls`}
 puts "so make it!!"
 exit
end


lines=File.readlines(filename)
print output=lines[0].chomp
File.open(filename,"w"){|f| lines[1..lines.length].each{|l| f.print l}}
