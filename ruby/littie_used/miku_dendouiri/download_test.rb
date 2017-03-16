require 'niconico'

 nico = Niconico.new('kokonidorobougadetazo@gmail.com','midokubonngaooi')
nico.login
$stdout = open("out.flv", "w")
puts nico.video("sm1715919").get_video
$stdout.flush

