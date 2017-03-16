require 'pp'

require 'digest/md5'

$md5_1='c627e19450db746b739f41b64097d449'
md5_2='31e101310bcd7fae974b921eb148099c'
response='c3077454ecf09ecef1d6c1201038cfaf'
password=''
username="q9"
realm="secret"
httpmethod='GET'
cnonce='9691c249745d94fc'
nonce="bbKtsfbABAA=5dad3cce7a7dd2c3335c9b400a19d6ad02df299b"
uri="/~q9/"
response="c3077454ecf09ecef1d6c1201038cfaf"
qop='auth'
nc='00000001'
cnonce="9691c249745d94fc"

a1 = username + ":" + realm + ":" + password
a2 = httpmethod + ":" + uri
#puts 'OK' if (Digest::MD5.hexdigest(a2)==md5_2)
#puts 'OK'if response == Digest::MD5.hexdigest(md5_1+":"+nonce+":"+nc+":"+cnonce+":"+qop+":"+md5_2 )



def bruteforceattack(n,string='')
username="q9"
realm="secret"
a1 = username + ":" + realm + ":" + string
#p string+x
if (n==0 && $md5_1 == Digest::MD5.hexdigest(a1)) then
puts 'password is '+string 
else
#p '.',string
#p Digest::MD5.hexdigest(a1)
end 
#puts 'string is '+string+' '+n.to_s if (n==0)

if(n>0) then
array=('a'..'z').to_a+('0'..'9').to_a+('A'..'Z').to_a
array.each do |x|
# p string,n
 bruteforceattack(n-1,string+x)
end 
end
end


#bruteforceattack(6,'FLAG_')
#puts 'END'




require 'rack/auth/digest/md5'

REALM  = 'the realm'

require 'digest/md5'
PWHASH = Digest::MD5.new.update('%s:%s:%s' % ['dayflower', REALM, 'password'])

use Rack::Auth::Digest::MD5,
  { 
    :realm            => REALM,
    :opaque           => '',
    :passwords_hashed => true,
  },''
  do |username|
#    PWHASH
	$dm5_1
  end




require 'net/http'

result = Net::HTTP.get('http://ksnctf.sweetduet.info:10080', '/~q9/')

p result

