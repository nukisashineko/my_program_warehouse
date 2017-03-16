#!/usr/bin/ruby 
# -*- coding : utf-8 -*-
require 'pp'
require 'gmail'
require 'open-uri'
require 'url'
require './splits'
require './read_html_to_txt'
require './twitter_tatodo2'

def getbody(mail)
  if !mail.text_part && !mail.html_part
   return  mail.body.decoded.encode("UTF-8", mail.charset)
  elsif mail.text_part
    return  mail.text_part.decoded
  elsif mail.html_part
    return  mail.html_part.decoded
  end
end

def ppgetbody(mail)
  if !mail.text_part && !mail.html_part
   return "body: " + mail.body.decoded.encode("UTF-8", mail.charset)
  elsif mail.text_part
    return "text: " + mail.text_part.decoded
  elsif mail.html_part
    return "html: " + mail.html_part.decoded
  end
end


def who_is_cokkie(to_addr)
end

def send_simple_mail(gmail,to_addr,url,body_str) 
  gmail.deliver do
   to to_addr
   subject url
   text_part do
     body body_str
   end
#  add_file "/path/to/some_image.jpg"
  end
end

def read_early_mail(gmail)
  gmail.inbox.emails(:unread).each do |email|
    email.mark(:read)
#    email.archive!
    return email
  end
end

def read_lately_mail(gmail)
  gmail.inbox.emails(:unread).reverse.each do |email|
    email.mark(:read)
#    email.archive!
    return email
  end
end


def email_split(gmail)
     email = read_lately_mail(gmail)
p "email.subject =#{email.subject}"
     from_addr = email.from.to_s.scan(/\"(.*?)\"/).flatten.join('@')
    return from_addr ,email.subject, getbody(email)
end

def get_html_page(url,flags={})
  temp=open(url).read
#  puts "when get_html ,=#{temp}"
#  File.open("temp.html","w"){|f| f.write(temp)}
  html_to_txt(temp,flags)
end

def read_mail(mail)
#件名、日付、From、To
    puts "Subject: #{mail.subject}"
    puts "Date: #{mail.date}"
    puts "From: #{mail.from}"
    puts "To: #{mail.to}"
    puts ppgetbody(mail)
end

def chack_url (url)
  i = 0
  while temp=/\.(.+)$/ =~ url[i+1...url.length]
    i += temp+1
  end
p "i=#{i} url[i...n]=#{url[i...url.length]}"
  return url[i...url.length]
end

def split_text(html)
  return split_ten_kilo_byte(splits(html,["\n"]))
end

def google_search(str)
  keyword = URI::escape(str)
#  puts "search keyword=#{keyword}"
  url = "http://www.google.com/search?hl=ja&lr=lang_ja&ie=UTF-8&oe=UTF-8&q=#{keyword}"
 return url
end

def send_bodys(gmail,to_addr,url,bodys)
      bodys.each_with_index do |body,n|
       send_simple_mail(gmail,to_addr,n.to_s+"_"+url,body)
      end
end

def get_html_and_allsend(gmail,to_addr,url,flags={})
      html = get_html_page(url,flags)
  #    p "html =  #{html}"
      puts "html=#{html}"
      bodys = split_text(html)
      send_bodys(gmail,to_addr,url,bodys)
      puts "send all complete !!"
end

def usually(gmail,to_addr,url)
  puts "it's usually case"
  case (chack_url(url))
    when '.img'
    puts "url is img file"

    else 
    puts "url is html or bugURL"
      get_html_and_allsend(gmail,to_addr,url)
#       get_file(url)
#       send_simple_mail(gmail,to_addr,url,body,img)
  end
#    p "to_addr =#{to_addr}"
end
def send_help(gmail,to_addr)
helps = []
helps <<'
***help***

command
-sub:url,(none)
|body:取得したいurlを入力

command
-sub:search
|body:google検索の実行

command
-sub:
|body:取得したいurlを入力

command
-sub:help
|body:これ
'
send_bodys(gmail,to_addr,"help",helps)
end

def gmail_func(user,pass)
Gmail.new(user,pass) do |gmail|
  while (true)
   unless(0 < gmail.inbox.count(:unread))
    puts "not exists unread mail"
  else
    while (0 < gmail.inbox.count(:unread))
      puts "exists unread mail."
      (to_addr,sub,body) = email_split(gmail)
      puts "body=#{body}"
      case sub
        when nil
          usually(gmail,to_addr,body)
        when "help"
          send_help(gmail,to_addr)
        when "search"
          puts "sub is search. Will start google search."
          get_html_and_allsend(gmail,to_addr,google_search(body),google: 'on')
        when "halt"
          system 'echo "halt";halt'
        when "exit"
         system 'echo "exit";exit'
	when 'tweet'
	  tatodo2_tweet(body)
        else
          p [sub]
          puts "not be  sub!!"
      end
    end
  end
  sleep(100)
end
end
end

