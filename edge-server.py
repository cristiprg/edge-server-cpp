import socket
import struct

remote_host = "0.0.0.0"
remote_port = 10000
RECV_BUFF = 512

# TCP Serving loop
def serve():
    local_sock = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
    local_sock.bind((remote_host, remote_port))
    local_sock.listen(1)
    print('Started serving on {}:{}'.format(remote_host, remote_port))

    while True:
        remote_conn, remote_addr = local_sock.accept()
        print('Accepted new connection request')

        try:
            while True:

                # Get the size of the point cloud
                request_data = remote_conn.recv(8)
                request_data_size = int(struct.unpack("q", request_data)[0])
                print ('request_data_size = {}'.format(request_data_size))

                point_cloud = remote_conn.recv(request_data_size)

                if(not len(request_data) or not len(point_cloud)):
                    #Close connection on empty request
                    break

                # #Send response
                # print('Sending response buffer:{}'.format(encoded_packet))
                # remote_conn.send(encoded_packet.encode(UTF8_ENCODING))

        finally:
            remote_conn.close()

serve()
