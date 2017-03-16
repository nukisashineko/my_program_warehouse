#!/usr/bin/ruby -w
# -*- coding : utf-8 -*-


require 'hpricot'
require 'open-uri'

doc = Hpricot( open("http://www.kmc.gr.jp/").read )

(doc/:a).each do |link|
  puts "#{link.inner_html} → #{link[:href]}"
end
