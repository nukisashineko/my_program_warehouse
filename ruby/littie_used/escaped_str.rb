#!/usr/bin/ruby
# -*- coding : utf-8 -*-

str='56&83<0 && 2>3'

escaped_str=str.gsub(/&/,'&amp;').gsub(/</,'&lt;').gsub(/>/,'&gt;')
p escaped_str
