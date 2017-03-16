#!/usr/bin/ruby -w
# -*- coding : utf-8 -*-


require 'xmlrpc/client'
client = XMLRPC::Client.new2("http://localhost:8080/")
p client.call("michael.add",5,3)
p client.call("michael.div",5,3)
