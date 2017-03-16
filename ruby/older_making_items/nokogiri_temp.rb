# -*- coding: utf-8 -*-
require 'nokogiri'

neko_index_path="./index.html"

index=""
File.open(neko_index_path) do |f|
  index=Nokogiri::HTML(f)
end

neko_all = index.xpath(".//a").map do |elm|
 elm["href"] if (elm['class']=='major' or elm['class']=='minor' )
end.compact

def neko_more_info(neko_name)
temp=""
File.open(neko_name) do |f|
 temp=Nokogiri::HTML(f)
end

array=[]

temp.css("ul").each do |elm|
if elm['class'] =="spec"
# p "spec"
 array <<  elm.css("li").map{|e| e.to_html.gsub(/<br>(.*?)<\/li>/,"\n**\\1**\n")}.join(',')
end
end

p array

temp.css("div").each do |elm|
case elm['id'] 
when "breed-name" then
# p "name" 
 array <<  elm.content
when "breed-photo" then
# p "photo" 
 array <<  elm.css('img')[0]['src']
end
end
array.concat (temp.css("div").map {|elm|  elm.content if elm['class'] =="message_body"}.compact!)

array.join(',').gsub(/\n/,"")
end

#p neko_more_info "abyssinian.html"

File.open("temp.cvs","w") do |f|
#f.puts neko_all.map{|neko| neko_more_info neko}.join(',')
end
