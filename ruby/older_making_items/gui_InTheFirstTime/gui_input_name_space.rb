#!/usr/bin/ruby -w
# -*- coding : utf-8 -*-
require 'tk'
TkLabel.new(nil,:text=>'ruby/Tk is cool').pack
f=TkFrame.new.pack
e=TkEntry.new(f,:width=>8,).pack(:side=>:right)
el=TkLabel.new(f,:text=>'nama: ').pack(:side=>:left)
l=TkLabel.new.pack
TkButton.new(nil,:text=>'exit',:command=>proc{exit}).pack(:side=>:right)
TkButton.new(nil,:text=>'Hi',:command=>proc{l.text("Hi,#{e.value}")}).pack(:side=>:left)
Tk.mainloop
