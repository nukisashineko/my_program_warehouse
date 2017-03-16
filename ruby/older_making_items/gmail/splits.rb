#!/usr/bin/ruby -w
# -*- coding : utf-8 -*-

def splits(var,string)
    var = [var] unless(var.class==Array)
    string = string.split("") unless(string.class==Array)
  _splits(var,string)
end

def _splits(vars,array)
  return vars if(array.length == 0)
  
#  p "vars =#{vars}"
#  p "vars.length =#{vars.length}"
   (0...vars.length).each {|i|
     vars[i]=vars[i].split(array[0])
  }
  return _splits(vars.flatten,array[1..array.length])
end

def split_ten_kilo_byte(array)
  ten_kilo_byte = 10**4
  sum  = i = 0
  result =[]
  starti= i
#p array
  until (i >= array.length)
    if(sum+array[i].bytesize>ten_kilo_byte)
p "sum=#{sum}"
      result << array[starti...i].join("\n")
      starti = i
      sum = 0
#p result
    end
        sum+=array[i].bytesize
#p "sum=#{sum}"
        i+=1
  end
    result << array[starti...array.length].join("\n")
  return result
end
