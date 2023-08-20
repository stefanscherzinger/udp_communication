#include <iostream>
#include <boost/asio.hpp>
#include "udp_communication/protocol.h"

using boost::asio::ip::udp;

int main() {
    constexpr int port = 9000;
    constexpr size_t msg_size = Message::size();

    boost::asio::io_service io_service;
    udp::socket socket(io_service);
    udp::endpoint endpoint(udp::v4(), port);

    // Bind the socket to the specified endpoint
    socket.open(endpoint.protocol());
    socket.bind(endpoint);

    while (true) {
        std::vector<uint8_t> buffer(msg_size);
        udp::endpoint sender_endpoint;

        size_t length = socket.receive_from(boost::asio::buffer(buffer), sender_endpoint);
        Message msg = Message::deserialize(buffer);

        std::cout << "Received " << length << " bytes from " << sender_endpoint << ": ";
        std::cout << msg.print() << std::endl;
    }

    return 0;
}
