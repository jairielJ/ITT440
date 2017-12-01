require 'socket'

puts "Connecting to #{ARGV[0]}:#{ARGV[1]}..."
socket = TCPSocket.open ARGV[0], ARGV[1]

socket.puts ARGV[2]
puts socket.gets
socket.close
