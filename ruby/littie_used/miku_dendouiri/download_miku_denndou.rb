# Rubyでニコニコの動画をダウンロードしてMP3にも変換する黒魔術　あたりが元サイトが見当たらない元ネタ。
require 'mechanize'
require 'niconico'
require 'time'
require 'systemu'

def measure(&block)
  t0 = Time.now
  ret = block.call
  span = Time.now - t0
  return ret, span
end
def web_scraping(&block)
  begin 
#    throw Mechanize::ResponseCodeError,'404'
    ret = block.call 
  rescue Mechanize::ResponseCodeError => e
    case e.response_code
    when "404"
      puts "  caught Net::HTTPNotFound !"
    when "502"
      puts "  caught Net::HTTPBadGateway !"
    else
      puts "  caught Excepcion !" + e.response_code
    end
  end
end

nico = Niconico.new('kokonidorobougadetazo@gmail.com','midokubonngaooi')
nico.login
url = "http://www5.atwiki.jp/hmiku/pages/4386.html"
m = Mechanize.new
m.get url
list = m.page.iframes.map{|e| e.src}.map{|e| e =~ /\/(sm[0-9]+)$/ ; $1}
list -= [nil] + Dir.glob("sm*.mp3").map{|x| x.gsub(".mp3","") }
#tmp =''
#list=list.drop_while{|x|x != (tmp = 'sm4141643') }
#list =[ tmp] +list
p list.length
p list
list.each{|e|
  web_scraping do 
        p "file is #{e}"
	video= nico.video(e)
        p "#{e} download"
	ret, time = measure do
		open("#{e}.flv", "w"){|f| f.write video.get_video  }
	end
	puts "download end.  time is %02d時%02d分%02d秒"%[time/(60*60),(time/60)%60,time%60]
	p command =  %Q(ffmpeg -y -i #{e}.flv #{e}.mp3)
	status,out,err = systemu command
        p status
  end
}

