#!/usr/bin/ruby -w
# -*- coding : utf-8 -*-

require 'xmlrpc/client'


def print_client_result(*arg)
client =XMLRPC::Client.new2("http://localhost:8080/")
  ok,result = client.call2(*arg)
  if ok
    puts result
  else
    puts "Error:#{result.faultCode}: #{result.faultString}"
  end
end


print_client_result("michael.add",5,3)
print_client_result("michael.add",5)



client =XMLRPC::Client.new2("http://localhost:8080/")
michael = client.proxy2("michael")
p michael.add(5,3)
p michael.div(5,3)
