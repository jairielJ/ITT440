require 'socket'
require 'timeout'

lbsock = TCPServer.open '', ARGV[0]

svrfile = File.new 'svrlist', 'r'
svrcount = 0
svrip = []
svrport = []
while line = svrfile.gets

if line.slice(0) == '#'
next
end
ip, port = line.split
svrip.push ip
svrport.push port
svrcount += 1
end

if svrcount == 0
puts 'svrlist is empty!'
exit 1
end

ttimeout = 2
loop do
clisock = lbsock.accept
svri = clisock.gets.to_i
puts svri
if svri > svrcount - 1 || svri <0
clisock.puts 'Index not in range of available servers...'
clisock.close
next
end
begin
svrsock = nil
Timeout.timeout(ttimeout) do
svrsock = TCPSocket.open svrip[svri]. svrport[svri]
end
rescue Timeout::Error
clisock.puts "Connection to server[#{svri}] timed out..."
clisock.close
next
end
clisock.puts svrsock.gets
svrsock.close
clisock.close
end
