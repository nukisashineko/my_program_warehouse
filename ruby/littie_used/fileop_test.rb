#!/usr/bin/ruby
# -*- coding : utf-8 -*-

File.open("use_test.txt",'a'){|f|
	f.puts Time.now
	$stdout=f
	puts "string write out in stdout."
	$stdout=STDOUT
}
