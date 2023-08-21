#include "boost/asio.hpp"
#include <chrono>
#include <stdexcept>
#include <thread>
#include "udp_communication/protocol.h"
#include <iostream>

using namespace boost::asio;

int main(int argc, char** argv)
{
  // User parameters
  int port = 9000;
  std::string remote_ip = "127.0.0.1";
  auto safe_convert = [&](const char* str) {
    try
    {
      return std::stoi(str);
    }
    catch (const std::invalid_argument& e)
    {
    }
    return port;
  };

  switch(argc)
  {
    case 2:
      port = safe_convert(argv[1]);
      break;
    case 3:
      port = safe_convert(argv[1]);
      remote_ip = argv[2];
      break;
    default:
      std::cout << "Usage: client [port [server-ip]]" << std::endl;
      break;
  }
  std::cout << "Sending to " << remote_ip << " on port: " << port << std::endl;

  io_service io_service;
  ip::udp::socket socket(io_service);
  ip::udp::endpoint remote_endpoint;

  socket.open(ip::udp::v4());

  remote_endpoint = ip::udp::endpoint(ip::address::from_string(remote_ip), port);

  boost::system::error_code err;

  constexpr double rate = 3.0;  // Hz
  uint32_t sequence_number = 0;

  while (true)
  {
    auto msg = Message();
    msg.sequence_number = sequence_number;
    msg.data = {0.1, 2.3, 3.4, 5.6};

    auto serialized_msg = msg.serialize();
    socket.send_to(buffer(serialized_msg, serialized_msg.size()), remote_endpoint, 0, err);
    ++sequence_number;

    std::this_thread::sleep_for(std::chrono::duration<double>(1.0 / rate));
  }

  socket.close();

  return 0;
}
