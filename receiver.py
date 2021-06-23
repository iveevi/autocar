import socket
import struct
import serial

# Setup serial
ser = serial.Serial('/dev/ttyACM0', 9600, timeout=1)
ser.flush()

# Setup socket
sock = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
sock.bind(('', 8080))
sock.listen(5)

print("host = " + socket.gethostname())
(client, address) = sock.accept()

print("Passed")

# Transfer loop
while True:
        chunk = '' + client.recv(4)

        num = struct.unpack('i', chunk[:4])[0]

        if num < 0:
                break
        
        ser.write(struct.pack('B', num))

print("Finished.")