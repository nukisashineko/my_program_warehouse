
class String
	def sjis_kana_to_roman()
	sjis_kana='゛ぬふあうえおやゆよわほほたていすかんなにらせ゜むーちとしはきくまのりれゃつさそひこみもねるめ'.scan(/./)
	sjis_roman="`1234567890-=qwertyuiop[]\\asdfghjkl;'zxcvbnm,./".scan(/./)
	sjis_kana_to_roman = Hash[sjis_kana.zip(sjis_roman)]
	sjis_roman_to_kana = Hash[sjis_roman.zip(sjis_kana)]
	return self.scan(/./).map{|c| sjis_kana_to_roman[c] }.join()
	end
	def sjis_roman_to_kana()
	sjis_kana='゛ぬふあうえおやゆよわほほたていすかんなにらせ゜むーちとしはきくまのりれゃつさそひこみもねるめ'.scan(/./)
	sjis_roman="`1234567890-=qwertyuiop[]\\asdfghjkl;'zxcvbnm,./".scan(/./)
	sjis_kana_to_roman = Hash[sjis_kana.zip(sjis_roman)]
	sjis_roman_to_kana = Hash[sjis_roman.zip(sjis_kana)]
	return self.scan(/./).map{|c| sjis_roman_to_kana[c] }.join()
	end
end

__FILE__
require 'romkan'
require './sjis_kana_to_roman'
p 'てちかちとにてらちにとにかいのなすいかちくにからくちもにみみみちとにみみしいにかかちみみしちのちすちとちほまにとなもらとにみちみちにか ららのちとににかららもらかかち'.sjis_kana_to_roman.to_kana
