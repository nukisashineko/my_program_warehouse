#!/usr/bin/ruby

(1...100).each do |i|
				case i % 15
				when 0				 then puts "fizzbuzz"
				when 3,6,9,12	then puts "fizz"
				when 5,10			then puts "buzz"
				else 							 puts i
				end
end

