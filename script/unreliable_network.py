#!/usr/bin/env python3

import socket
import random
import threading

def forward_packets(client_address, server_address):
    client_socket = socket.socket(socket.AF_INET, socket.SOCK_DGRAM)
    server_socket = socket.socket(socket.AF_INET, socket.SOCK_DGRAM)

    client_socket.bind(client_address)

    while True:
        data, sender_addr = client_socket.recvfrom(1024)

        server_socket.sendto(data, server_address)

        # Simulate packet duplication with a 20% probability
        if random.random() < 0.2:
            print("sending doubled message")
            for _ in range(2):
                server_socket.sendto(data, server_address)


def main():
    client_address = ('127.0.0.1', 9000)
    server_address = ('127.0.0.1', 9001)

    # Start a thread to forward packets from client to server
    forward_thread = threading.Thread(target=forward_packets, args=(client_address, server_address))
    forward_thread.start()

    print("Packet forwarding started...")

    try:
        forward_thread.join()
    except KeyboardInterrupt:
        print("\nPacket forwarding stopped.")

if __name__ == "__main__":
    main()
