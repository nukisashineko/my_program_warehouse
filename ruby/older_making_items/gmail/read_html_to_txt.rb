#!/usr/bin/ruby -w
# -*- coding : utf-8 -*-

require 'cgi'



def html_to_txt(str,flags={})	
  str = CGI.unescapeHTML(str)
  str = str.gsub(/\r?\t?/,"")
  str = str.gsub(/\n/,"")
  str = str.gsub(/<br.*?>/i,"\n")
  str = str.gsub(/<cite>(.*?)<\/cite>/m,"\nhttp://\\1\n") if(flags[:google])
  str = str.gsub(/<a href="(http:\/\/.*?)".*?>/m,"\n$..\\1..$\n") unless(flags[:google])
  str = str.gsub(/<a href="(.*?)".*?>/m,"\n$..http://\\1..$\n") unless(flags[:google])
  str = str.gsub(/(<script.*?script>)/m,"")
  str = str.gsub(/(<pre.*?pre>)/m,"")
  str = str.gsub(/(<style.*?style>)/m,"")
  str = str.gsub(/(<?php.*?>)/m,"")
  str = str.gsub(/<(\!--.*?--)>/m,"")
  str = str.gsub(/<.*?>/m,"")
  return str
end

def html_to_txt_debug(str,flags={})	
  str = CGI.unescapeHTML(str)
  str = str.gsub(/\r?\t?/,"")
  str = str.gsub(/\n/,"")
  str = str.gsub(/<br.*?>/i,"___\n")
  str = str.gsub(/<cite>(.*?)<\/cite>/m,"\nhttp://\\1\n") if(flags[:google])
  str = str.gsub(/<a href="(.*?)".*?>/m,"\n$..\\1\..$n") unless(flags[:google])
  str = str.gsub(/(<script.*?script>)/m,"\n{~~\\1~~}\n")
  str = str.gsub(/(<pre.*?pre>)/m,"\n[--\\1--]\n")
  str = str.gsub(/(<style.*?style>)/m,"\n?++\\1++?\n")
  str = str.gsub(/(<?php.*?>)/m,"\n(__\\1__)\n")
  str = str.gsub(/<(\!--.*?--)>/m,"\n|**\\1**|\n")
  str = str.gsub(/<(.*?)>/m,"\n@\\1@\n")
  return str
end


#puts html_to_txt_debug(File.read("temp.html"),google: 'on')
