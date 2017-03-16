require 'systemu'
date = %q(sleep 2; ruby -e"  t = Time.now; STDOUT.puts t; STDERR.puts t  " )
systemu 'sleep 5' do |pid|
sleep 3 
p 'test'
Process.kill 9, pid # 1秒後に kill 
end
p 'wait'
status, stdout, stderr = systemu date
p 'nekoneko'
p [ status, stdout, stderr ]
p 'dogdog'
