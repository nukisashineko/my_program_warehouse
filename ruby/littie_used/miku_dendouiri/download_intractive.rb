#!/usr/bin/env ruby
# coding: utf-8

require 'thor'
require 'yaml'
require 'niconico'

class Niconicodl < Thor
	default_command :download

	desc 'download', 'download video'
	option :sm,  :type => :string,  :aliases => '-s', :desc => "sm number"
	option :mp3, :type => :boolean, :aliases => '-m', :desc => "mp3 convert"
	def download
		# ダウンロードする動画のIDを決定する
		if options[:sm] then
			id = options[:sm]
		else
			id = ask "sm number: "
		end

		# ログインするまで
		user = YAML.load_file(File.expand_path(File.dirname(__FILE__)+"/user.yml"))
		niconico = Niconico.new(user["mail"], user["pass"])
		niconico.login

		# 動画の取得
		video = niconico.video(id)

		# 動画の保存
		$stdout = open("#{id}.flv", "w")
		puts video.get_video
		$stdout.flush

		# -m オプションがあった場合はMP3に変換
		p `ffmpeg -y -i #{id}.flv #{id}.mp3` if options[:mp3]
	end
end

Niconicodl.start

#使い方

# 動画をダウンロードする（ダウンロードしたい動画のID(sm***)を対話的に入力）
#./niconicodl

# 動画をダウンロードする
#./niconicodl -s sm******

# 動画をダウンロードして、MP3に変換する
#./niconicodl -s sm****** -m


