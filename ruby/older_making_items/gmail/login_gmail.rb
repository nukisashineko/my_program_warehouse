#!/usr/bin/ruby -w
# -*- coding : utf-8 -*-
require 'pp'
require 'gmail'
require 'uri'
require 'addressable/uri'
require 'cgi'

user = "<gmailuser>"
pass = "<gmailpass>"
to_addr = "<mail to address>"
subject = "Having fun in Puerto Rico!"
str_body = "<p>Text of <em>html</em> message.</p>"
uri = URI.parse("mailto:#{to_addr}?subject=test&body=test'sbody")
a_uri = Addressable::URI.parse("mailto:#{to_addr}?subject=#{subject}&body=#{str_body}").normalize

def getbody(email)
  if !mail.text_part && !mail.html_part
   retrun "body: " + mail.body.decoded.encode("UTF-8", mail.charset)
  elsif mail.text_part
    retrun "text: " + mail.text_part.decoded
  elsif mail.html_part
    retrun "html: " + mail.html_part.decoded
  end 
end

def test(user,pass)
  Gmail.new(user,pass) do |gmail|
  #  p  gmail.inbox.count
  #  p  gmail.inbox.count(:unread)
  #
  #  gmail.inbox.emails(:unread).each do |email|
  #    email.mark(:read)
  #    email.archive!
  #    email.label("Faxes")
  #  end
    gmail.deliver do
     to "amazyaku.is.fish0danya-@ezweb.ne.jp"
     subject "Having fun in Puerto Rico!"
     text_part do
       body "Text of \n\n plaintext \r\n  message."
     end
#     html_part do
#      content_type 'text/html; charset=UTF-8'
#      body "<p>Text of <em>html</em> message.</p>" + '<a href="http://google.com">go to google</a>'
#     end
  #  add_file "/path/to/some_image.jpg"
    end
  
  #  mails =  gmail.inbox.emails(:unread).map do |mail|
  ##件名、日付、From、To
  #    puts "Subject: #{mail.subject}"
  #    puts "Date: #{mail.date}"
  #    puts "From: #{mail.from}"
  #    puts "To: #{mail.to}"
  #    puts getbody(mail)
  #  end
  end
end
def test2(user,pass)
  Gmail.new(user,pass) do |gmail|
    gmail.deliver do
     to to_addr
     subject subject
     text_part do
       body "Text of plaintext message."
     end
     html_part do
      content_type 'text/html; charset=S-JIS'
      body  "<a href=\"#{uri}\">uri\n</a>"+"<a href=\"#{a_uri}\">a_uri\n</a>"
     end
    add_file "../../temp.html"
    end
  end
end

def test3(user,pass)
  Gmail.new(user,pass) do |gmail|
    gmail.deliver do
     to to_addr
     subject subject
     text_part do
       body "Text of plaintext message. http://google.com"
     end
    end
  end
end

test(user,pass)
#p "%s:%s\n%s\n" %[uri.scheme,uri.to,uri.headers.map{|a| if a.class==Array then a.join('=') else CGI.encode(a) end}.join('&amp;')]

#p URI.escape('http://www.example.com/hyonyarara/?abc=まり&も&def=阿寒湖')
