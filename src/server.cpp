#include <iostream>
#include <boost/asio.hpp>
#include <ostream>

using boost::asio::ip::udp;

int main() {
    constexpr int port = 9000;
    constexpr int datagram_size = 1024;

    boost::asio::io_service io_service;
    udp::socket socket(io_service);
    udp::endpoint endpoint(udp::v4(), port);

    // Bind the socket to the specified endpoint
    socket.open(endpoint.protocol());
    socket.bind(endpoint);

    while (true) {
        char data[datagram_size];
        udp::endpoint sender_endpoint;

        size_t length = socket.receive_from(boost::asio::buffer(data), sender_endpoint);

        std::cout << "Received " << length << " bytes from " << sender_endpoint << ": ";
        std::cout << data << std::endl;
    }

    return 0;
}
