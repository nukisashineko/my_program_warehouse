#!/usr/bin/ruby -w
# -*- coding : utf-8 -*-

 require 'mechanize'
 require 'kconv' #あとでUTF-8を扱うので

hatena_user="nekorare"
hatena_pass="matatabihayamete"


 agent = WWW::Mechanize.new
 diary_page = agent.get("http://d.hatena.ne.jp/nekorare/")
 login_link = diary_page.link_with(:text=>"ログイン")
 login_page = login_link.click


 login_form = login_page.forms.first
 login_form['key'] = hatena_user
 login_form['password'] = hatena_pass
 redirect_page = agent.submit(login_form)
 diary_link = redirect_page.links.text("こちら".toutf8)
 diary_page = agent.get(diary_link.href)
 edit_link = diary_page.links.text("日記を書く".toeuc)
 edit_page = agent.get(edit_link.href)
 edit_form = edit_page.forms.name("edit").first
 edit_form["body"] += "\n*Rubyから日記を更新してみるテスト。"
 ok_button = edit_form.buttons.name("edit")
 agent.submit(edit_form, ok_button)


