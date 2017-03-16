#!/bin/sh
exec ruby -x "$0" "$@"
#!ruby
# -*- coding : utf-8 -*-

("a".."i").methods
decoder={}
("a".."i").each_with_index do |x,index|
decoder.update ({x=>index})
end
("k".."z").each_with_index do |x,index|
decoder.update ({x=>index})
end
decoder.update ({"j"=>24})


encoder={}
("a".."i").each_with_index do |x,index|
encoder.update ({index=>x})
end
("k".."z").each_with_index do |x,index|
encoder.update ({index=>x})
end
encoder.update ({24=>"j"})

def it_equal?(x,char)
  return (x==char) unless x.class==Array
  return (x[0]==char || x[1]==char)
end


def encode(arg)
 str=""
 arg.split(/../).each do |x|
  str<<encoder[x.to_int]
 end
 return str
end

def decode(arg)
 array=[]
 arg.split(//).each do |x|
  array<<decoder[x]
 end
 return array 
end
p decoder["k"]
p "Polybius squar" or "ポリビオスの換字表"
text="2443412542"
crypt=encode(text)
p decode("romio")
puts "text=#{text} ,crypt=#{crypt.to_s},decode=#{decode(crypt).to_s}"
