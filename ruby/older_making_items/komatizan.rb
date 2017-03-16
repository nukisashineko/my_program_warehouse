#!/bin/sh
exec ruby -x "$0" "$@"
#!ruby
# -*- coding : utf-8 -*-

class Komatizan 
def func(n,str)


	if (n==10 && eval(str)==100)
p str+"=#{eval(str)}"
		return false
	end
	ans=false
	if (n <10)
        ans ||= func(n+1,str+n.to_s) 
        ans ||= func(n+1,str+"+"+n.to_s) 
        ans ||= func(n+1,str+"-"+n.to_s)
	end 
	return ans

end
end

 a=Komatizan.new 
p a.func(1,"")
