#include <boost/asio.hpp>
#include <iostream>
#include <stdexcept>
#include <string>
#include <unordered_map>

#include "udp_communication/protocol.h"

using boost::asio::ip::udp;

int main(int argc, char ** argv)
{
  // User parameters
  const int port = [&] {
    switch (argc) {
      case 2:
        try {
          return std::stoi(argv[1]);
        } catch (const std::invalid_argument & e) {
        }
      default:
        std::cout << "Usage: server [port]" << std::endl;
        return 9001;
    }
  }();

  std::cout << "Listening on port: " << port << std::endl;

  constexpr size_t msg_size = Message::size();

  // Open a UDP-based port for clients.
  boost::asio::io_service io_service;
  udp::socket socket(io_service);
  udp::endpoint endpoint(udp::v4(), port);
  socket.open(endpoint.protocol());
  socket.bind(endpoint);

  // Use a hash map to filter doubled messages
  std::unordered_map<uint32_t, Message> received_msgs;

  // Counter to assure message ordering
  uint32_t counter = 0;

  while (true) {
    std::vector<uint8_t> buffer(msg_size);
    udp::endpoint sender_endpoint;

    socket.receive_from(boost::asio::buffer(buffer), sender_endpoint);
    Message msg = Message::deserialize(buffer);

    // Only keep messages that we haven't seen so far
    if (received_msgs.find(msg.sequence_number) == received_msgs.end()) {
      received_msgs[msg.sequence_number] = msg;
    } else {
      std::cout << "Dropping doubled message: " << msg.sequence_number << std::endl;
    }

    // Process all messages that have sequential ordering
    while (received_msgs.find(counter) != received_msgs.end()) {
      std::cout << "Processing message: " << msg.sequence_number << std::endl;
      received_msgs.erase(msg.sequence_number);
      ++counter;
    }
  }

  return 0;
}
