#!/usr/bin/ruby -w
# -*- coding : utf-8 -*-

require 'tk'
TkLabel.new(nil,
	:text => 'Hello,world!',
	:fg   => 'green',
	:bg   => 'black').pack
TkButton.new(nil,
	:text => 'Exit',
	:command => proc{exit}).pack
Tk.mainloop
