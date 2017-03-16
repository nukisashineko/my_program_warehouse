#!/usr/bin/ruby -w
# -*- coding : utf-8 -*-
require "tk"



root = TkRoot.new() { title "More Widgets" }
frame = TkFrame.new(root).pack("side"=>"right","fill"=>"y")
buttons = TkFrame.new(frame).pack("side"=>"bottom")
load = TkButton.new(buttons) { text "Load" }
save = TkButton.new(buttons) { text "Save" }
TkGrid.configure(load, save,)

display = TkFrame.new(root).pack("side"=>"left")
editor = TkText.new(display).pack() # top
status = TkLabel.new(display) { text "launching..." }
status.pack("side"=>"bottom", "anchor"=>"w")
list = TkListbox.new(frame).pack()
list.insert("end", "/some/file")
list.insert("end", "/etc/hosts")

list.pack("fill"=>"y")
display.pack("fill"=>"both", "expand"=>true)
editor.pack("fill"=>"both", "expand"=>true)
list.pack("expand"=>true)

Tk.mainloop
