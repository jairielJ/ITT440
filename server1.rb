require 'socket'

# listen and bind are involved in TCPSserver. initialze
server_socket=TCPServer.new '192.168.220.132',57175

client, client_sockaddr = server_socket.accept 

data = client.recvfrom( 20 )[0].chomp
puts " Jai say '#{data}'"

client.puts "You said: #{data}"

sleep 1

server_socket.close
