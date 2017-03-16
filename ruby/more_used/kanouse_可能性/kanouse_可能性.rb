#!/bin/sh
exec ruby -x "$0" "$@"
#!ruby
# -*- coding : utf-8 -*-

require 'scanf'
class MyRand2Percent


def set_percent_to_rand()
	(0...@a.length).each do |i|
	(0...i).each{|j|  @a[j].percent += @a[i].percent}
	end
end

def scan_from_file(file)
	x , y= "" , 0
	File.open(file,"r") do |f|
	f.each do |line| 
		x, y= line.scanf("%s %d")
		@a.push @temp.new(x,y)
	end
	end
end

def myrand()
	n=rand(@a[0].percent)
	result=false 
	@a.each  do |x|
	if  x.percent <= n+1 then 
		result = x.name
		break
 	end
	end
	result||="????"
	p n if result=="????"
	return result
end

def initialize (file)
	@temp=Struct.new("Rand2Method",:name,:percent);
	@a=[]
	scan_from_file(file)
	set_percent_to_rand()
	puts "#{file} isn't 100%. It is #{@a[0].percent}%."  if @a[0].percent !=100
end

end

def main 
	a=[]
	n=ARGV[0].to_i
	temp=ARGV[1,ARGV.length]
	temp.each do |filename|
		a << MyRand2Percent.new(filename)
	end
	n.times do
		a.each{|x| puts x.myrand()}
		puts	""
	end

end

#temp=MyRand2Percent.new("temp.txt");	
#hash= Hash.new(0)
#1000.times{ hash[temp.myrand()]+=1}
#p hash


main()

