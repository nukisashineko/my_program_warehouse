#!/bin/sh
exec ruby -x "$0" "$@"
#!ruby
# -*- coding : utf-8 -*-

require 'digest/md5'

$testarray="abcdefghijklmnopqrstuvwxyz"
$testarray=$testarray+$testarray.upcase
$testarray<<"123456789"
$testarray=$testarray.split(//)


def usage()
 puts "$0 <user> <passwd> <realm> <qop> <http method> <URI> <nonce> <nc> <cnonce>"
 puts "if $nonce or $nc or $cnonce is none then you shuold write nil."
 puts "and argc =="+ARGV.length.to_s
 exit
end

usage() unless ARGV.length ==9

$user = ARGV[0]
$passwd = ARGV[1]
$realm = ARGV[2]
$qop = ARGV[3]
$http_method = ARGV[4]
$uri = ARGV[5]
$nonce = (ARGV[6]!="nil")?ARGV[6]:""
$nc = (ARGV[7]!="nil")?ARGV[7]:""
$cnonce = (ARGV[8]!="nil")?ARGV[8]:""

if true
$http_method="GET"
$user="q9"
$realm="secret"
$nonce="bbKtsfbABAA=5dad3cce7a7dd2c3335c9b400$a19d6ad02df299b"
$uri="/~q9/"
$response="c3077454ecf09ecef1d6c1201038cfaf"
made_response= Digest::MD5.new
made_response<<"c627e19450db746b739f41b64097d449:bbKtsfbABAA=5dad3cce7a7dd2c3335c9b400$a19d6ad02df299b:00000001:9691c249745d94fc:auth:31e101310bcd7fae974b921eb148099c"
$qop="auth"
$nc="00000001"
$cnonce="9691c249745d94fc"
p $response
p made_response.to_s
end

puts "$user=#{$user}"
puts "$passwd=#{$passwd}"
puts "$realm=#{$realm}"
puts "$qop=#{$qop}"
puts "$http_method=#{$http_method}"
puts "$uri=#{$uri}"
puts "$nonce=#{$nonce}"
puts "$nc =#{$nc }"
puts "$cnonce=#{$cnonce}"


$digest = Digest::MD5.new
$a1 = Digest::MD5.new
$a2 = Digest::MD5.new



p $a1<<$user+":"+$realm+":"+$passwd
p $a2<<$http_method+$uri
p $digest<<$a1.to_s+":"+$nonce+":"+$nc+":"+$cnonce+":"+$qop+":"+$a2.to_s


def incremental_search(n)
 1.upto(n) do |c|
  result=incremental_search2("",c)
  return result if result
 end
end

def incremental_search2(str,n)
return nil if n==0
 $testarray
$testarray.each do |a|
 $passwd="FLAG_"+str+a
 $a1<<$user+":"+$realm+":"+$passwd
 $digest<<$a1.to_s+":"+$nonce+":"+$nc+":"+$cnonce+":"+$qop+":"+$a2.to_s
 if $digest.to_s == $response
 p $passwd
 return $passwd;
 end
end
$testarray.each do |a|
  result=incremental_search2(str+a,n-1)
  return result if result
end
return nil
end

