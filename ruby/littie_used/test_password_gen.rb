#!/usr/bin/ruby
# -*- coding : utf-8 -*-

def password_gen(size=8)
	[*0..9,*'a'..'z',*'A'..'Z'].sample(size).join
end

puts 10.times.map { password_gen }
