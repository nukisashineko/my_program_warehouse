#!/bin/sh
exec ruby -x "$0" "$@"
#!ruby
# -*- coding : utf-8 -*-


list="
a   AAAAA   g    AABBA     m    ABABB   s    BAAAB     y    BABBA
b   AAAAB   h    AABBB     n    ABBAA   t    BAABA     z    BABBB
c   AAABA   i    ABAAA     o    ABBAB   u    BAABB 
d   AAABB   j    BBBAA     p    ABBBA   v    BBBAB
e   AABAA   k    ABAAB     q    ABBBB   w    BABAA
f   AABAB   l    ABABA     r    BAAAA   x    BABAB"


list=list.split(" ")
temp={}
i=0

until list[i]==nil or list[i+1]==nil
 temp[list[i]]=list[i+1]
 i+=2
end
p ARGV[0].split('').map{|c| temp[c]}.join(' ')
